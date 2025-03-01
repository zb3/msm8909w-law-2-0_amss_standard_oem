#===============================================================================
#
# Copyright (c) 2014 Qualcomm Technologies, Inc. All Rights Reserved.
# Qualcomm Technologies Proprietary and Confidential.
#
#=============================================================================== 

"""Parses the config file specific to secimage. Provides all the
functionalities from :mod:`sectools.common.utils.c_config`. Once the config is parsed,
a tree representation of the object is created.
"""


import os

import defines as defines

from sectools.common.utils import c_config, c_path
from sectools.common.utils.c_logging import logger
from sectools.common.utils.c_misc import get_dups_in_list
from sectools.common.crypto.common_classes import HmacParams


class ConfigDir(object):
    """Processes a given config directory to discover the available secimage
    config files in the directory.
    
    :param str config_dir: Path to the directory containing the config files.
    """
    
    def __init__(self, config_dir):
        """Initializations and checks"""
        if not c_path.validate_dir(config_dir):
            raise RuntimeError('Directory doesnt exist: ' + config_dir)
        
        # First level of directory that is expected
        sub_config_dir = c_path.join(config_dir, defines.CONFIG_DIR_BASENAME)
        try:    
            c_path.validate_dir(sub_config_dir)
        except Exception as e:
            raise RuntimeError('Directory ' + config_dir + '\n'
                               '    ' + 'must contain configs sub directory: ' + defines.CONFIG_DIR_BASENAME)
                 
        self.config_dir = sub_config_dir
        
    def _get_config_path(self, chipset_dir):
        """Returns the config found in the chipset dir matching
        the naming conventions. If the config file is not found
        in the dir, None is returned.
        
        :param str chipset_dir: The directory in which to look for config path.
        :returns: config_file
        :rtype: (str) 
        """
        config = None
        chipset_from_dir_name = os.path.basename(chipset_dir)
        
        for entry in os.listdir(chipset_dir):
            path = c_path.join(chipset_dir, entry)
            if c_path.validate_file(path) and entry.endswith(defines.XML_NAME_ENDING):
                # Extract the chipset from the file
                try:
                    chipset_from_file = ConfigParser.get_chipset_from_file(path)
                except Exception as e:
                    logger.debug2('Skipping file: ' + entry + '\n'
                                  '    ' + 'Failed to load the file: ' + str(e))
                    continue
                
                # Check the naming conventions
                if chipset_from_file == chipset_from_dir_name:
                    config = path
                else:                    
                    logger.debug2('Skipping file: ' + entry + '\n'
                                  '    ' + 'Chipset from file: "' + chipset_from_file + '" does not match chipset from dir name: "' + chipset_from_dir_name + '"')
            else:
                logger.debug2('Skipping file: ' + entry + '\n'
                              '    ' + 'Name does not match any of the naming convention patters')                    
        logger.debug2('Config path found for chipset_dir: ' + chipset_dir + '\n'
                      '    ' + 'config: ' + str(config))
        return config
        
    @property
    def config_paths(self):
        """(list[tuple(str)]) List of the config paths found in the workspace
        conforming to the naming structure.
        """
        config_dir = self.config_dir
        config_paths = []
        
        logger.debug('Searching config path sets in dir: ' + config_dir)
        for entry in os.listdir(config_dir):
            path = c_path.join(config_dir, entry)
            if c_path.validate_dir(path):
                config = self._get_config_path(path)    
                if config:
                    config_paths.append(config)
                else:
                    logger.debug2('Skipping dir: ' + entry + '\n'
                                  '    ' + 'Does not contain any configs')
            else:
                logger.debug2('Skipping file in first level: ' + entry)
        logger.debug('Config paths found from the config dir: ' + str(config_paths))
        return config_paths
    
    @property
    def configs(self):
        """(list[obj]) List of objects of :class:`ConfigParser` generated by
        loading the config files in the config_dir.
        """
        configs = []
        for path in self.config_paths:
            logger.debug2('Loading config: ' + path)
            try:
                configs.append(ConfigParser(path))
            except Exception as e:
                logger.warning('Failed to load config: ' + path + '\n'
                               '    ' + 'Error: ' + str(e))
        return configs
    
    @property
    def chipsets(self):
        """(list[str]) List of chipset names supported by the configs in the
        config dir.
        """
        chipsets = []
        for config in self.configs:
            chipsets.append(config.chipset)
        logger.debug('Chipsets found from the configs: ' + str(chipsets))
        return chipsets
    
    @config_paths.setter
    def config_paths(self, value):
        raise RuntimeError('Config_Paths in a config dir cannot be set.')
    
    @configs.setter
    def configs(self, value):
        raise RuntimeError('Configs in a config dir cannot be set.')
    
    @chipsets.setter
    def chipsets(self, value):
        raise RuntimeError('Chipsets in a config dir cannot be set.')
    
    def get_chipset_dir(self, chipset):
        """Returns the expected path within the config dir for the chipset
        
        :param str chipset: The chipset for which directory path is queried.
        """
        return c_path.join(self.config_dir, chipset)
    
    def create_chipset_dir(self, chipset):
        """Creates the directory in the config dir for the chipset
        
        :param str chipset: The chipset for which directory needs to be
            created
        :raises: RuntimeError - If directory creation fails
        """
        try:
            c_path.create_dir(self.get_chipset_dir(chipset))
        except Exception as e:
            raise RuntimeError('Failed to create directory for chipset: ' + chipset + '\n'
                               '    ' + 'Error: ' + str(e))
        
    def get_chipset_config_path(self, chipset):
        """
        :param str chipset: chipset to return config file for
        :returns: config path corresponding to the given chipset
        :rtype: str
        """ 
        logger.debug('Searching configs corresponding to chipset: ' + chipset)
        chipset_dir = c_path.join(self.config_dir, chipset)
        
        if c_path.validate_dir(chipset_dir):
            return self._get_config_path(chipset_dir)
        raise RuntimeError('Did not find config for chipset: "' + chipset + '"')
    

class ConfigParser(c_config.CoreConfig):
    """Parses the SecImage configuration file using c_config.CoreConfig and
    the module auto-generated using generateDS (auto_gen_xml_config).
    
    :param str config_path: Path to the config file to be parsed.
    
    .. data: root
    
        Root class representing the structure of the config file.
    
    .. data:: __version__ = 1.1
    
        Version of the Config Parser
        
    """
    
    __version__ = '1.1' 
    
    def __init__(self, config_path):
        """Initializations and checks"""
        import auto_gen_xml_config, auto_gen_obj_config

        assert isinstance(config_path, str)
        self.config_module = auto_gen_xml_config
        self.obj_module = auto_gen_obj_config
        c_config.CoreConfig.__init__(self, self.config_module, config_path)
        self.validate()
        
    def validate(self):
        """Normalizes and validates the data in the secimage xml.
        
        :raises: RuntimeError if config is determined to be invalid
        """
        c_config.CoreConfig.validate(self, defines.CONFIG_STRUCTURE)
        
        # Validate root config rules
        from rule import ConfigRulesManager
        rules = ConfigRulesManager()
        rules.validate(self, defines.CONFIG_STRUCTURE)
        
        # Check that the version matches
        config_version = self.version 
        if config_version != self.__version__:
            raise RuntimeError('Version of parser: "' + self.__version__ + '" does not match version from config "' + config_version + '"')
        
        # Check that atleast one image_type was provided
        image_type_id_list = [image_type.id for image_type in self._get_parsegen_image_type_list()]
        if len(image_type_id_list) == 0:
            raise RuntimeError('Config file must contain at least one image_type under parsegen->image_types_list')
        
        # Check that the ids of the image_type objects are unique
        dup_image_type_id_list = get_dups_in_list(image_type_id_list)
        if len(dup_image_type_id_list):
            raise RuntimeError('image_type ids must be unique. Found multiple image_types with same id: ' + str(dup_image_type_id_list))
        
        # Check that the ids of the cert_configs_list are unique
        cert_config_id_list = [cert_config.id for cert_config in self._get_signing_local_cert_config_list()]
        dup_cert_config_id_list = get_dups_in_list(cert_config_id_list)
        if len(dup_cert_config_id_list):
            raise RuntimeError('cert_config ids must be unique. Found multiple cert_configs with same id: ' + str(dup_cert_config_id_list))
        
        # Check that atleast one image was provided
        sign_id_list = self.sign_id_list
        if len(sign_id_list) == 0:
            raise RuntimeError('Config file must contain at least one image under the images_list')
        
        # Check that the ids of the image objects are unique
        dup_sign_id_list = get_dups_in_list(sign_id_list)
        if len(dup_sign_id_list):
            raise RuntimeError('image sign_ids must be unique. Found multiple images with the same sign_id: ' + str(dup_sign_id_list))
        
    def generate(self, file_path):
        """Generates the secimage config file with the current configuration
        of the root node.
        
        :param str file_path: path to the config file that should be generated
            with the current data 
        """
        logger.note('Generating config file...')
        c_config.CoreConfig.generate(self, file_path,
                                     defines.XML_ROOTNODE,
                                     defines.XML_NAMESPACE,
                                     defines.XML_PREPEND_LINES) 
        logger.note('Generated config file at: ' + str(file_path))       
        
    def transfer_from_obj(self, obj):
        """Updates the values of the config root node using the attributes of
        the object provided. 
        
        :param Cfg_Secimage obj: Object to be used for obtaining the values.
        """
        assert isinstance(obj, self.obj_module.Cfg_Secimage)
        logger.debug('Updating config contents using object: ' + obj)
        self.root = self.transfer_from_obj_to_node(obj,
                                                   self.root,
                                                   defines.CONFIG_STRUCTURE,
                                                   defines.ROOTNODE_NAME)
        logger.debug('Config contents updated.')

    def transfer_to_obj(self, obj):
        """Updates the attributes of the object provided using the values of the
        root config node. 
        
        :params: same as :meth:`transfer_from_obj` 
        """
        assert isinstance(obj, self.obj_module.Cfg_Secimage)
        logger.debug('Updating object using config contents: ' + obj)
        obj = self.transfer_from_node_to_obj(self.root,
                                             obj,
                                             defines.CONFIG_STRUCTURE,
                                             defines.ROOTNODE_NAME,)
        logger.debug('Object updated using the config.')
        
    def transfer_from_obj_to_node(self, obj, node, structure, structure_parent):
        return self.transfer(obj,
                             node,
                             structure,
                             structure_parent,
                             self.config_module,
                             defines.XML_CLASSNAME_GEN)
        
    def transfer_from_node_to_obj(self, node, obj, structure, structure_parent):
        return self.transfer(node,
                             obj,
                             structure,
                             structure_parent,
                             self.obj_module,
                             defines.OBJ_CLASSNAME_GEN)
    
    @property
    def chipset(self):
        """
        :returns: Name of the chipset.
        :rtype: str
        """
        return self.root.metadata.chipset
    
    @property
    def version(self):
        """
        :returns: Version of the config file.
        :rtype: str
        """
        return self.root.metadata.version
    
    @property
    def config_data(self):
        """
        :returns: Config object
        :rtype: obj
        """
        return self.root
    
    @property
    def sign_id_list(self):
        """
        :returns: sign_ids available in the config file
        :rtype: list[str]
        """
        return [image.sign_id for image in self._get_image_list()]
    
    def get_sign_id_for_image_name(self, image_name):
        """
        :param str image_name: Image name for which the sign id is needed.
        :returns: sign_id corresponding to the image_name provided.
        :rtype: str
        :raises RuntimeError: If None or multiple sign_ids are found for the
            given image_name.
        """
        assert isinstance(image_name, str)
        
        # Look for all the matching sign ids
        sign_ids_found = []
        for image in self._get_image_list():
            if image.name and image.name.lower() == image_name.lower():
                sign_ids_found.append(image.sign_id) 
                
        # Raise error if None or multiple sign ids are found
        if len(sign_ids_found) == 0:
            raise RuntimeError('Sign Id not found for image name: ' + image_name)
        elif len(sign_ids_found) > 1:
            raise RuntimeError('Multiple sign ids found for image name: ' + image_name + '\n'
                               '    ' + 'Sign Ids: ' + str(sign_ids_found))
        else:
            return sign_ids_found[0]
        
    def get_config_for_sign_id(self, sign_id):
        """
        :param str sign_id: Sign id for which the config block is needed.
        :returns: config block corresponding to the sign_id provided.
        :rtype: obj
        :raises RuntimeError: If sign_id does not correspond to a config block.
        """
        assert isinstance(sign_id, str)
        for image in self._get_image_list():
            if image.sign_id == sign_id:
                return image
        raise RuntimeError('Config block not found for sign id: ' + sign_id)
    
    def get_hmac_params_from_config(self, sign_id):
        """
        :returns: A HMAC object with the HMAC parameters from the config file.
        :rtype: obj
        """
        sign_id_config_block=self.get_config_for_sign_id(sign_id)
        msm_part = self.root.signing.default_attributes.msm_part
        oem_id = self.root.signing.default_attributes.oem_id
        model_id= self.root.signing.default_attributes.model_id
        msm_id = msm_part + oem_id[2:] + model_id[2:]
        msm_id = int(msm_id,16)
        sw_id = sign_id_config_block.signing_attributes_overrides.sw_id
        sw_id = int(sw_id,16)
        return HmacParams(msm_id,sw_id)
        
    def _get_image_list(self):
        """
        :returns: list of image objects from the config file
        :rtype: list[obj]
        """
        return self.root.images_list.image
    
    def _get_parsegen_image_type_list(self):
        """
        :returns: list of image_type objects from the config file
        :rtype: list[obj]
        """
        return self.root.parsegen.image_types_list.image_type
    
    def _get_signing_local_cert_config_list(self):
        """
        :returns: list of cert_config objects from the config file
        :rtype: list[obj]
        """
        return self.root.signing.signer_attributes.local_signer_attributes.cert_configs_list.cert_config
    
    def _set_signing_local_cert_config_list(self, cert_config_nodes_list):
        """
        :param cert_config_nodes_list: list[auto_gen_xml_config.complex_cert_config]
        """
        assert isinstance(cert_config_nodes_list, list)
        for cert_config in cert_config_nodes_list:
            assert isinstance(cert_config, self.config_module.complex_cert_config)
        self.root.signing.signer_attributes.local_signer_attributes.cert_configs_list.cert_config = cert_config_nodes_list
        
    @classmethod
    def get_chipset_from_file(self, path):
        return ConfigParser(path).chipset
    
    
#------------------------------------------------------------------------------
# Restrict all import
#------------------------------------------------------------------------------
__all__ = ['ConfigDir',
           'ConfigParser',
           'defines',
           'auto_gen_obj_config']
