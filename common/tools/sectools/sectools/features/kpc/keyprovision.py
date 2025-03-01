#===============================================================================
#
# Copyright (c) 2014 Qualcomm Technologies, Inc. All Rights Reserved.
# Qualcomm Technologies Proprietary and Confidential.
#
#===============================================================================

"""Provides a command line interface to the services provided by kpc.

.. data:: KEYPROVISION_TOOL_NAME

    Name of the tool

.. data:: KEYPROVISION_TOOL_VERSION

    Version of the tool

.. data:: DEF_KEYPROVISION_OUTPUT_DIR_NAME

    Name of the default output directory

.. data:: DEF_KEYPROVISION_OUTPUT_DIR_PATH

    Absolute path of the default output directory
"""

import sys
import traceback

from sectools.common.utils import c_path
from sectools.common.utils.c_base import dynamicToolStatus, CoreOptionParser
from sectools.common.utils.c_logging import logger
from sectools.features.kpc.kpc import KeyProvisionCore


# Tool name for command arg
CMD_ARG_TOOL_NAME = 'keyprovision'

# Name & version of the tool
KEYPROVISION_TOOL_NAME = 'KeyProvision'
KEYPROVISION_TOOL_VERSION = '2.0'

# Path definitions
DEF_KEYPROVISION_OUTPUT_DIR_PATH = dynamicToolStatus.toolDir

__version__ = KEYPROVISION_TOOL_NAME + ' ' + KEYPROVISION_TOOL_VERSION


class KeyProvisionOptionParser(CoreOptionParser):
    """Parses and validates the command line arguments specific to KeyProvision."""

    _LIST_TAG = 'LIST'

    @property
    def c_description(self):
        """(str) Returns the description of the program."""
        return 'This program generates & validates the sec.dat file.'

    @property
    def c_version(self):
        """(str) Returns the version of the program."""
        return __version__

    def c_add_options(self):
        """Adds the command line args supported by keyprovision."""
        # Generating secdat
        gen_group = self.add_option_group('Generating sec.dat with or without secdat as input')
        gen_group.add_option('-u', '--user_config_path', metavar='<file>',
                             help='path to the user config file.')
        gen_group.add_option('-e', '--keymap_config_path', metavar='<file>',
                             help='path to the keyprovision mapping config file.')
        gen_group.add_option('-s', '--secdat', metavar='<file>',
                             help='path to the sec dat file as input for common_output or for validation.')
        gen_group.add_option('-p', '--platform', metavar='<platform>',
                             help='specify the platform, to get the config files as input related to platform')

        # Specifying the output location
        output_group = self.add_option_group('Specifying output location')
        output_group.add_option('-o', '--output_dir', metavar='<dir>',
                                help='directory to store output files. DEFAULT: "./"',
                                default=DEF_KEYPROVISION_OUTPUT_DIR_PATH)

        # Specifying the operation
        operations_group = self.add_option_group('Operations')
        operations_group.add_option('-g', '--generate', action='store_true',
                                    default=False, help='1. generates the sec.dat file using config files and the cmd is  "-u, -e, -g" '
                                                        '2. generates the sec.dat file using config files & input secdat and the cmd is "-u, -e, -g, -s" '
                                                        '3. generates the sec.dat file using platform and the cmd is "-p <platform> '
                                                        '4. generates the sec.dat file using platform & input secdat and the cmd is "-p <platform> -s')
        operations_group.add_option('-a', '--validate', action='store_true',
                                    default=False,
                                    help='validate the sec.dat file and the cmd is "-u, -e, -a, -s')
        operations_group.add_option('-l', '--verify_inputs', action='store_true',
                                    default=False,
                                    help='verify the command line options.')

    def c_validate(self):
        """Validates the command line args provided by the user.

        :raises: RuntimeError
        """
        args = self.parsed_args
        err = []

        if not args.platform:
            # Check the config paths
            if args.user_config_path and not args.keymap_config_path:
                err.append('Please provide the keymap config files using '
                           '--oem_config_path along with the user config file.')
            if not (args.keymap_config_path):
                err.append('Please provide the config files using '
                           '--user_config_path, --keymap_config_path, '
                           'or provide the platform details using -p <platform> ')

            # Check and sanitize any paths for read access
            for path in ['user_config_path', 'keymap_config_path']:
                path_val = getattr(args, path, None)
                if path_val:
                    path_val = c_path.normalize(path_val)
                    if not c_path.validate_file(path_val):
                        err.append('Cannot access ' + path + ' at: ' + path_val)
                    setattr(args, path, path_val)

        if args.platform and (args.keymap_config_path or args.user_config_path):
            err.append('Please provide either config files or platform as a input. '
                       'Please do not provide both types of input for generation of sec.dat')

        # Check the operations
        if not (args.generate or args.validate or args.verify_inputs):
            err.append('Please specify one or more operations to perform.')
        if args.validate and not args.generate:
            if not args.secdat:
                err.append('Please provide path to the secdat file using -s for validation.')

        # Check and sanitize any paths for read access
        for path in ['secdat']:
            path_val = getattr(args, path, None)
            if path_val:
                path_val = c_path.normalize(path_val)
                if not c_path.validate_file(path_val):
                    err.append('Cannot access ' + path + ' at: ' + path_val)
                setattr(args, path, path_val)

        # Check and sanitize paths for write access
        for path in ['output_dir']:
            path_val = getattr(args, path, None)
            if path_val:
                path_val = c_path.normalize(path_val)
                try:
                    c_path.create_dir(path_val)
                except Exception as e:
                    err.append('Cannot write at: ' + path_val + '\n'
                               '    ' + 'Error: ' + str(e))
                setattr(args, path, path_val)

        # Raise error if any
        if err:
            if len(err) > 1:
                err = [('  ' + str(idx + 1) + '. ' + error) for idx, error in enumerate(err)]
                err = 'Please check the command line args:\n\n' + '\n'.join(err)
            else:
                err = err[0]
            raise RuntimeError(err)

def log_to_file(folder):
    """Configures the logger to log to filesystem

    :param str folder: Directory to generate the logs in.
    """
    folder = c_path.normalize(folder)
    try:
        c_path.create_dir(folder)
    except Exception as e:
        raise RuntimeError('Unable to create directory for logging: ' + folder + '\n'
                           '    ' + 'Error: ' + str(e))
    logger.enable_file_logging(KEYPROVISION_TOOL_NAME, num_logs=1, log_dir=folder)

def print_summary():
    """Prints the summary of the actions performed by KeyProvision"""
    # TODO: Print the summary
    pass

def main(args):
    """Parses the command line arguments, performs any basic operations based on
    the parsed arguments and starts processing using the fbc module.
    """
    # Log to file
    log_to_file(c_path.join(args.output_dir, KeyProvisionCore.FEATURE_DIR))

    # Print the tool's launch command
    logger.debug('\n\n    KeyProvision launched as: "' + ' '.join(sys.argv) + '"\n')

    # Initialize KeyProvisionCore
    kpc = KeyProvisionCore(debug=args.debug)

    # Configure KeyProvisionCore
    if (args.keymap_config_path):
        kpc.set_config_paths(args.keymap_config_path, None, None, args.user_config_path)
    elif args.platform:
        kpc.set_config_paths(*kpc._config_dir_obj.get_chipset_config(args.platform))

    if (args.secdat):
        kpc.secdat = args.secdat

    kpc.output_dir = c_path.join(args.output_dir)

    # Process
    kpc.process(verify_setup=args.verify_inputs,
                generate=args.generate,
                validate=args.validate)

    # Print summary of operations
    print_summary()

def parse_args(argv):
    return KeyProvisionOptionParser(argv).parsed_args

if __name__ == '__main__':
    try:
        # Call the main of the tool
        main(parse_args(sys.argv))

    except Exception:
        logger.debug(traceback.format_exc())
        logger.error(sys.exc_info()[1])
        sys.exit(1)

    except KeyboardInterrupt:
        print
        logger.error('Keyboard Interrupt Received. Exiting!')
        sys.exit(1)

    sys.exit(0)


