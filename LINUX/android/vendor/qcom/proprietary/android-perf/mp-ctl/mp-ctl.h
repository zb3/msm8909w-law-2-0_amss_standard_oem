/******************************************************************************
  @file    mp-ctl.h
  @brief   Header file for communication and actions for PerfLock

  DESCRIPTION

  ---------------------------------------------------------------------------
  Copyright (c) 2011-2015 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
  ---------------------------------------------------------------------------
******************************************************************************/

#ifndef __MP_CTL_H__
#define __MP_CTL_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Server functions */
int  mpctl_server_init(void);
void mpctl_server_exit(void);

/* Client function (up to 0-7)*/
#define MPCTL_CMD_PERFLOCKACQ 2
#define MPCTL_CMD_PERFLOCKREL 3
#define MPCTL_CMD_PERFLOCKPOLL 4
#define MPCTL_CMD_PERFLOCKRESET 5
#define MPCTL_CMD_PERFLOCK_PROFILE 6
#define MPCTL_CMD_PERFLOCK_RESTORE_GOV_PARAMS 7

/*newer resources
  supported from v3.0 onwards*/
#define MAX_RESOURCES_PER_REQUEST 16
#define MAX_ARGS_PER_REQUEST (MAX_RESOURCES_PER_REQUEST*2)
enum {
    MPCTLV3_MIN_FREQ_CLUSTER_BIG_CORE_0                 = 0x40800000,
    MPCTLV3_MIN_FREQ_CLUSTER_BIG_CORE_1                 = 0x40800010,
    MPCTLV3_MIN_FREQ_CLUSTER_BIG_CORE_2                 = 0x40800020,
    MPCTLV3_MIN_FREQ_CLUSTER_BIG_CORE_3                 = 0x40800030,
    MPCTLV3_MIN_FREQ_CLUSTER_LITTLE_CORE_0                 = 0x40800100,
    MPCTLV3_MIN_FREQ_CLUSTER_LITTLE_CORE_1                 = 0x40800110,
    MPCTLV3_MIN_FREQ_CLUSTER_LITTLE_CORE_2                 = 0x40800120,
    MPCTLV3_MIN_FREQ_CLUSTER_LITTLE_CORE_3                 = 0x40800130,

    MPCTLV3_MAX_FREQ_CLUSTER_BIG_CORE_0                 = 0x40804000,
    MPCTLV3_MAX_FREQ_CLUSTER_BIG_CORE_1                 = 0x40804010,
    MPCTLV3_MAX_FREQ_CLUSTER_BIG_CORE_2                 = 0x40804020,
    MPCTLV3_MAX_FREQ_CLUSTER_BIG_CORE_3                 = 0x40804030,
    MPCTLV3_MAX_FREQ_CLUSTER_LITTLE_CORE_0                 = 0x40804100,
    MPCTLV3_MAX_FREQ_CLUSTER_LITTLE_CORE_1                 = 0x40804110,
    MPCTLV3_MAX_FREQ_CLUSTER_LITTLE_CORE_2                 = 0x40804120,
    MPCTLV3_MAX_FREQ_CLUSTER_LITTLE_CORE_3                 = 0x40804130,

    MPCTLV3_SCHED_BOOST                               = 0x40C00000,
    MPCTLV3_SCHED_PREFER_IDLE                         = 0x40C04000,
    MPCTLV3_SCHED_MIGRATE_COST                        = 0x40C08000,
    MPCTLV3_SCHED_SMALL_TASK                          = 0x40C0C000,
    MPCTLV3_SCHED_MOSTLY_IDLE_LOAD                    = 0x40C10000,
    MPCTLV3_SCHED_MOSTLY_IDLE_NR_RUN                  = 0x40C14000,
    MPCTLV3_SCHED_INIT_TASK_LOAD                      = 0x40C18000,
    MPCTLV3_SCHED_UPMIGRATE                           = 0x40C1C000,
    MPCTLV3_SCHED_DOWNMIGRATE                         = 0x40C20000,
    MPCTLV3_SCHED_MOSTLY_IDLE_FREQ                    = 0x40C24000,
    MPCTLV3_SCHED_GROUP                               = 0x40C28000,
    MPCTLV3_SCHED_SPILL_NR_RUN                        = 0x40C2C000,
    MPCTLV3_SCHED_STATIC_CPU_PWR_COST                 = 0x40C30000,
    MPCTLV3_SCHED_RESTRICT_CLUSTER_SPILL              = 0x40C34000,
    MPCTLV3_SCHED_FREQ_AGGR_GROUP                     = 0x40C38000,
    MPCTLV3_SCHED_CPUSET_TOP_APP                      = 0x40C3C000,
    MPCTLV3_SCHED_CPUSET_FOREGROUND                   = 0x40C40000,
    MPCTLV3_SCHED_CPUSET_SYSTEM_BACKGROUND            = 0x40C44000,
    MPCTLV3_SCHED_CPUSET_BACKGROUND                   = 0x40C48000,
    MPCTLV3_SCHED_SET_FREQ_AGGR                       = 0x40C4C000,
    MPCTLV3_SCHED_ENABLE_THREAD_GROUPING              = 0x40C50000,

    MPCTLV3_MIN_ONLINE_CPU_CLUSTER_BIG                  = 0x41000000,
    MPCTLV3_MIN_ONLINE_CPU_CLUSTER_LITTLE               = 0x41000100,
    MPCTLV3_MAX_ONLINE_CPU_CLUSTER_BIG                  = 0x41004000,
    MPCTLV3_MAX_ONLINE_CPU_CLUSTER_LITTLE               = 0x41004100,

    MPCTLV3_ABOVE_HISPEED_DELAY_INTERACTIVE_CLUSTER_BIG = 0x41400000,
    MPCTLV3_BOOST_INTERACTIVE_CLUSTER_BIG               = 0x41404000,
    MPCTLV3_BOOSTPULSE_INTERACTIVE_CLUSTER_BIG          = 0x41408000,
    MPCTLV3_BOOSTPULSE_DURATION_INTERACTIVE_CLUSTER_BIG = 0x4140C000,
    MPCTLV3_GO_HISPEED_LOAD_INTERACTIVE_CLUSTER_BIG     = 0x41410000,
    MPCTLV3_HISPEED_FREQ_INTERACTIVE_CLUSTER_BIG        = 0x41414000,
    MPCTLV3_IO_IS_BUSY_INTERACTIVE_CLUSTER_BIG          = 0x41418000,
    MPCTLV3_MIN_SAMPLE_TIME_INTERACTIVE_CLUSTER_BIG     = 0x4141C000,
    MPCTLV3_TARGET_LOADS_INTERACTIVE_CLUSTER_BIG        = 0x41420000,
    MPCTLV3_TIMER_RATE_INTERACTIVE_CLUSTER_BIG          = 0x41424000,
    MPCTLV3_TIMER_SLACK_INTERACTIVE_CLUSTER_BIG         = 0x41428000,
    MPCTLV3_MAX_FREQ_HYSTERESIS_INTERACTIVE_CLUSTER_BIG = 0x4142C000,
    MPCTLV3_USE_SCHED_LOAD_INTERACTIVE_CLUSTER_BIG      = 0x41430000,
    MPCTLV3_USE_MIGRATION_NOTIF_CLUSTER_BIG             = 0x41434000,
    MPCTLV3_IGNORE_HISPEED_NOTIF_CLUSTER_BIG            = 0x41438000,

    MPCTLV3_ABOVE_HISPEED_DELAY_INTERACTIVE_CLUSTER_LITTLE = 0x41400100,
    MPCTLV3_BOOST_INTERACTIVE_CLUSTER_LITTLE               = 0x41404100,
    MPCTLV3_BOOSTPULSE_INTERACTIVE_CLUSTER_LITTLE          = 0x41408100,
    MPCTLV3_BOOSTPULSE_DURATION_INTERACTIVE_CLUSTER_LITTLE = 0x4140C100,
    MPCTLV3_GO_HISPEED_LOAD_INTERACTIVE_CLUSTER_LITTLE     = 0x41410100,
    MPCTLV3_HISPEED_FREQ_INTERACTIVE_CLUSTER_LITTLE        = 0x41414100,
    MPCTLV3_IO_IS_BUSY_INTERACTIVE_CLUSTER_LITTLE          = 0x41418100,
    MPCTLV3_MIN_SAMPLE_TIME_INTERACTIVE_CLUSTER_LITTLE     = 0x4141C100,
    MPCTLV3_TARGET_LOADS_INTERACTIVE_CLUSTER_LITTLE        = 0x41420100,
    MPCTLV3_TIMER_RATE_INTERACTIVE_CLUSTER_LITTLE          = 0x41424100,
    MPCTLV3_TIMER_SLACK_INTERACTIVE_CLUSTER_LITTLE         = 0x41428100,
    MPCTLV3_MAX_FREQ_HYSTERESIS_INTERACTIVE_CLUSTER_LITTLE = 0x4142C100,
    MPCTLV3_USE_SCHED_LOAD_INTERACTIVE_CLUSTER_LITTLE      = 0x41430100,
    MPCTLV3_USE_MIGRATION_NOTIF_CLUSTER_LITTLE             = 0x41434100,
    MPCTLV3_IGNORE_HISPEED_NOTIF_CLUSTER_LITTLE            = 0x41438100,

    MPCTLV3_CPUBW_HWMON_MIN_FREQ                      = 0x41800000,
    MPCTLV3_CPUBW_HWMON_DECAY_RATE                    = 0x41804000,
    MPCTLV3_CPUBW_HWMON_IO_PERCENT                    = 0x41808000,
    MPCTLV3_CPUBW_HWMON_HYST_OPT                      = 0x4180C000,
    MPCTLV3_CPUBW_HWMON_LOW_POWER_CEIL_MBPS           = 0x41810000,
    MPCTLV3_CPUBW_HWMON_LOW_POWER_IO_PERCENT          = 0x41814000,
    MPCTLV3_CPUBW_HWMON_MAX_FREQ                      = 0x41818000,
    MPCTLV3_CPUBW_HWMON_POLLING_INTERVAL              = 0x4181C000,
    MPCTLV3_CPUBW_HWMON_SAMPLE_MS                     = 0x41820000,
    MPCTLV3_CPUBW_HWMON_IDLE_MBPS                     = 0x41824000,

    MPCTLV3_VIDEO_ENCODE_PB_HINT                      = 0x41C00000,
    MPCTLV3_VIDEO_DECODE_PB_HINT                      = 0x41C04000,
    MPCTLV3_VIDEO_DISPLAY_PB_HINT                     = 0x41C08000,

    MPCTLV3_KSM_RUN_STATUS                            = 0x42000000,
    MPCTLV3_KSM_PARAMS                                = 0x42004000,

    MPCTLV3_SAMPLING_RATE_ONDEMAND                    = 0x42400000,
    MPCTLV3_IO_IS_BUSY_ONDEMAND                       = 0x42404000,
    MPCTLV3_SAMPLING_DOWN_FACTOR_ONDEMAND             = 0x42408000,
    MPCTLV3_SYNC_FREQ_ONDEMAND                        = 0x4240C000,
    MPCTLV3_OPTIMAL_FREQ_ONDEMAND                     = 0x42410000,
    MPCTLV3_ENABLE_STEP_UP_ONDEMAND                   = 0x42414000,
    MPCTLV3_MAX_INTERMEDIATE_STEPS_ONDEMAND           = 0x42418000,
    MPCTLV3_NOTIFY_ON_MIGRATE                         = 0x4241C000,

    MPCTLV3_GPU_POWER_LEVEL                           = 0X42800000,
    MPCTLV3_GPU_MIN_POWER_LEVEL                       = 0X42804000,
    MPCTLV3_GPU_MAX_POWER_LEVEL                       = 0X42808000,

    MPCTLV3_IRQ_BALANCER                              = 0X42C04000,
    MPCTLV3_UNSUPPORTED                               = 0X42C00000,
    MPCTLV3_INPUT_BOOST_RESET                         = 0x42C08000,
    MPCTLV3_SWAP_RATIO                                = 0x42C0C000,
    MPCTLV3_STORAGE_CLK_SCALING_DISABLE               = 0x42C10000,
    MPCTLV3_KEEP_ALIVE                                = 0x42C14000,
    MPCTLV3_PMQOS                                     = 0x42C18000,
};

enum major_resource_opcode {
    DISPLAY_OFF_MAJOR_OPCODE = 0,  /* 0x0 */
    POWER_COLLAPSE_MAJOR_OPCODE,   /* 0x1 */
    CPUFREQ_MAJOR_OPCODE,          /* 0x2 */
    SCHED_MAJOR_OPCODE,            /* 0x3 */
    CORE_HOTPLUG_MAJOR_OPCODE,     /* 0x4 */
    INTERACTIVE_MAJOR_OPCODE,      /* 0x5 */
    CPUBW_HWMON_MAJOR_OPCODE,      /* 0x6 */
    VIDEO_MAJOR_OPCODE,            /* 0x7 */
    KSM_MAJOR_OPCODE,              /* 0x8 */
    ONDEMAND_MAJOR_OPCODE,         /* 0x9 */
    GPU_MAJOR_OPCODE,              /* 0xA */
    MISC_MAJOR_OPCODE,             /* 0xB */
    MAX_MAJOR_RESOURCES
};

//do not change order of "resource minor groups"
enum minor_resource_opcode {
    DISPLAY_OFF_OPCODE = 0,
    MAX_DISPLAY_MINOR_OPCODE,

    POWER_COLLAPSE_OPCODE = 0,   /*0x0*/
    MAX_PC_MINOR_OPCODE,

    CPUFREQ_MIN_FREQ_OPCODE = 0, /* 0x0 */
    CPUFREQ_MAX_FREQ_OPCODE,     /* 0x1 */
    MAX_CPUFREQ_MINOR_OPCODE,

    SCHED_BOOST_OPCODE = 0,          /* 0x0 */
    SCHED_PREFER_IDLE_OPCODE,        /* 0x1 */
    SCHED_MIGRATE_COST_OPCODE,       /* 0x2 */
    SCHED_SMALL_TASK_OPCODE,         /* 0x3 */
    SCHED_MOSTLY_IDLE_LOAD_OPCODE,   /* 0x4 */
    SCHED_MOSTLY_IDLE_NR_RUN_OPCODE, /* 0x5 */
    SCHED_INIT_TASK_LOAD_OPCODE,     /* 0x6 */
    SCHED_UPMIGRATE_OPCODE,          /* 0x7 */
    SCHED_DOWNMIGRATE_OPCODE,        /* 0x8 */
    SCHED_MOSTLY_IDLE_FREQ_OPCODE,   /* 0x9 */
    SCHED_GROUP_OPCODE,              /* 0xA */
    SCHED_SPILL_NR_RUN_OPCODE,       /* 0xB */
    SCHED_STATIC_CPU_PWR_COST_OPCODE,/* 0xC */
    SCHED_RESTRICT_CLUSTER_SPILL_OPCODE,/* 0xD */
    SCHED_FREQ_AGGR_GROUP_OPCODE,       /* 0xE */
    SCHED_CPUSET_TOP_APP_OPCODE,     /* 0xF */
    SCHED_CPUSET_FOREGROUND_OPCODE,  /* 0x10 */
    SCHED_CPUSET_SYSTEM_BACKGROUND_OPCODE, /* 0x11 */
    SCHED_CPUSET_BACKGROUND_OPCODE,  /* 0x12 */
    SCHED_SET_FREQ_AGGR_OPCODE,      /* 0x13 */
    SCHED_ENABLE_THREAD_GROUPING_OPCODE,   /* 0x14 */
    MAX_SCHED_MINOR_OPCODE,

    CORE_HOTPLUG_MIN_CORE_ONLINE_OPCODE = 0,
    CORE_HOTPLUG_MAX_CORE_ONLINE_OPCODE,
    MAX_CORE_HOTPLUG_MINOR_OPCODE,

    INTERACTIVE_ABOVE_HISPEED_DELAY_OPCODE = 0,  /* 0x0 */
    INTERACTIVE_BOOST_OPCODE,                    /* 0x1 */
    INTERACTIVE_BOOSTPULSE_OPCODE,               /* 0x2 */
    INTERACTIVE_BOOSTPULSE_DURATION_OPCODE,      /* 0x3 */
    INTERACTIVE_GO_HISPEED_LOAD_OPCODE,          /* 0x4 */
    INTERACTIVE_HISPEED_FREQ_OPCODE,             /* 0x5 */
    INTERACTIVE_IO_IS_BUSY_OPCODE,               /* 0x6 */
    INTERACTIVE_MIN_SAMPLE_TIME_OPCODE,          /* 0x7 */
    INTERACTIVE_TARGET_LOADS_OPCODE,             /* 0x8 */
    INTERACTIVE_TIMER_RATE_OPCODE,               /* 0x9 */
    INTERACTIVE_TIMER_SLACK_OPCODE,              /* 0xA */
    INTERACTIVE_MAX_FREQ_HYSTERESIS_OPCODE,      /* 0xB */
    INTERACTIVE_USE_SCHED_LOAD_OPCODE,           /* 0xC */
    INTERACTIVE_USE_MIGRATION_NOTIF_OPCODE,      /* 0xD */
    INTERACTIVE_IGNORE_HISPEED_NOTIF_OPCODE,     /* 0xE */
    MAX_INTERACTIVE_MINOR_OPCODE,

    CPUBW_HWMON_MINFREQ_OPCODE = 0,
    CPUBW_HWMON_DECAY_RATE_OPCODE,
    CPUBW_HWMON_IO_PERCENT_OPCODE,
    CPUBW_HWMON_HYST_OPT_OPCODE,
    CPUBW_HWMON_LOW_POWER_CEIL_MBPS,
    CPUBW_HWMON_LOW_POWER_IO_PERCENT,
    CPUBW_HWMON_MAXFREQ_OPCODE,
    CPUBW_HWMON_POLLING_INTERVAL_OPCODE,
    CPUBW_HWMON_SAMPLE_MS,
    CPUBW_HWMON_IDLE_MBPS,
    MAX_CPUBW_HWMON_MINOR_OPCODE,

    VIDEO_ENCODE_PB_HINT = 0,
    VIDEO_DECODE_PB_HINT,
    VIDEO_DISPLAY_PB_HINT,
    MAX_VIDEO_MINOR_OPCODE,

    KSM_ENABLE_DISABLE_OPCODE = 0,
    KSM_SET_RESET_OPCODE,
    MAX_KSM_MINOR_OPCODE,

    OND_SAMPLING_RATE_OPCODE = 0,
    OND_IO_IS_BUSY_OPCODE,
    OND_SAMPLING_DOWN_FACTOR_OPCODE,
    OND_SYNC_FREQ_OPCODE,
    OND_OPIMAL_FREQ_OPCODE,
    OND_ENABLE_STEP_UP,
    OND_MAX_INTERMEDIATE_STEPS,
    NOTIFY_ON_MIGRATE,
    MAX_OND_MINOR_OPCODE,

    GPU_POWER_LEVEL = 0,
    GPU_MIN_POWER_LEVEL,
    GPU_MAX_POWER_LEVEL,
    MAX_GPU_MINOR_OPCODE,

    UNSUPPORTED_OPCODE = 0,
    IRQ_BAL_OPCODE,
    INPUT_BOOST_RESET_OPCODE,
    SWAP_RATIO_OPCODE,
    STORAGE_CLK_SCALING_DISABLE_OPCODE,
    NET_KEEP_ALIVE_OPCODE,
    PMQOS_OPCODE,
    MAX_MISC_MINOR_OPCODE,

    MAX_MINOR_RESOURCES = MAX_DISPLAY_MINOR_OPCODE + MAX_PC_MINOR_OPCODE +
                          MAX_CPUFREQ_MINOR_OPCODE + MAX_SCHED_MINOR_OPCODE +
                          MAX_CORE_HOTPLUG_MINOR_OPCODE + MAX_INTERACTIVE_MINOR_OPCODE +
                          MAX_CPUBW_HWMON_MINOR_OPCODE + MAX_VIDEO_MINOR_OPCODE +
                          MAX_KSM_MINOR_OPCODE + MAX_OND_MINOR_OPCODE + MAX_GPU_MINOR_OPCODE +
                          MAX_MISC_MINOR_OPCODE
};

enum map_type {
    NO_VALUE_MAP = 0,
    VALUE_MAPPED = 1
};

/* Enum for pre-defined cluster map.
 * */
enum predefine_cluster_map {
    START_PRE_DEFINE_CLUSTER = 8,
    LAUNCH_CLUSTER = 8,
    SCROLL_CLUSTER = 9,
    ANIMATION_CLUSTER = 10,
    PREDEFINED_CLUSTER_11 = 11,
    PREDEFINED_CLUSTER_12 = 12,
    PREDEFINED_CLUSTER_13 = 13,
    PREDEFINED_CLUSTER_14 = 14,
    PREDEFINED_CLUSTER_15 = 15,
    MAX_PRE_DEFINE_CLUSTER
};

/* Enum for value mapping for frequency.
 * A target needs to define the mapped
 * values for these.
 * */
enum freq_map {
    LOWEST_FREQ = 0,
    LEVEL1_FREQ = 1,
    LEVEL2_FREQ = 2,
    LEVEL3_FREQ = 3,
    HIGHEST_FREQ = 4,
    FREQ_MAP_MAX
};

/*older resources
 *   supported till v2.0*/

enum resources {
    DISPLAY = 0,
    POWER_COLLAPSE,
    CPU0_MIN_FREQ,
    CPU1_MIN_FREQ,
    CPU2_MIN_FREQ,
    CPU3_MIN_FREQ,
    UNSUPPORTED_0,
    CLUSTR_0_CPUS_ON,
    CLUSTR_0_MAX_CORES,
    UNSUPPORTED_2,
    UNSUPPORTED_3,
    SAMPLING_RATE,
    ONDEMAND_IO_IS_BUSY,
    ONDEMAND_SAMPLING_DOWN_FACTOR,
    INTERACTIVE_TIMER_RATE,
    INTERACTIVE_HISPEED_FREQ,
    INTERACTIVE_HISPEED_LOAD,
    SYNC_FREQ,
    OPTIMAL_FREQ,
    SCREEN_PWR_CLPS,
    THREAD_MIGRATION,
    CPU0_MAX_FREQ,
    CPU1_MAX_FREQ,
    CPU2_MAX_FREQ,
    CPU3_MAX_FREQ,
    ONDEMAND_ENABLE_STEP_UP,
    ONDEMAND_MAX_INTERMEDIATE_STEPS,
    INTERACTIVE_IO_BUSY,
    KSM_RUN_STATUS,
    KSM_PARAMS,
    SCHED_BOOST,
    CPU4_MIN_FREQ,
    CPU5_MIN_FREQ,
    CPU6_MIN_FREQ,
    CPU7_MIN_FREQ,
    CPU4_MAX_FREQ,
    CPU5_MAX_FREQ,
    CPU6_MAX_FREQ,
    CPU7_MAX_FREQ,
    CPU0_INTERACTIVE_ABOVE_HISPEED_DELAY,
    CPU0_INTERACTIVE_BOOST,
    CPU0_INTERACTIVE_BOOSTPULSE,
    CPU0_INTERACTIVE_BOOSTPULSE_DURATION,
    CPU0_INTERACTIVE_GO_HISPEED_LOAD,
    CPU0_INTERACTIVE_HISPEED_FREQ,
    CPU0_INTERACTIVE_IO_IS_BUSY,
    CPU0_INTERACTIVE_MIN_SAMPLE_TIME,
    CPU0_INTERACTIVE_TARGET_LOADS,
    CPU0_INTERACTIVE_TIMER_RATE,
    CPU0_INTERACTIVE_TIMER_SLACK,
    CPU4_INTERACTIVE_ABOVE_HISPEED_DELAY,
    CPU4_INTERACTIVE_BOOST,
    CPU4_INTERACTIVE_BOOSTPULSE,
    CPU4_INTERACTIVE_BOOSTPULSE_DURATION,
    CPU4_INTERACTIVE_GO_HISPEED_LOAD,
    CPU4_INTERACTIVE_HISPEED_FREQ,
    CPU4_INTERACTIVE_IO_IS_BUSY,
    CPU4_INTERACTIVE_MIN_SAMPLE_TIME,
    CPU4_INTERACTIVE_TARGET_LOADS,
    CPU4_INTERACTIVE_TIMER_RATE,
    CPU4_INTERACTIVE_TIMER_SLACK,
    CLUSTR_1_MAX_CORES,
    SCHED_PREFER_IDLE,
    SCHED_MIGRATE_COST,
    SCHED_SMALL_TASK,
    SCHED_MOSTLY_IDLE_LOAD,
    SCHED_MOSTLY_IDLE_NR_RUN,
    SCHED_INIT_TASK_LOAD,
    VIDEO_DECODE_PLAYBACK_HINT,
    DISPLAY_LAYER_HINT,
    VIDEO_ENCODE_PLAYBACK_HINT,
    CPUBW_HWMON_MIN_FREQ,
    CPUBW_HWMON_DECAY_RATE,
    CPUBW_HWMON_IO_PERCENT,
    CPU0_INTERACTIVE_MAX_FREQ_HYSTERESIS,
    CPU4_INTERACTIVE_MAX_FREQ_HYSTERESIS,
    GPU_DEFAULT_PWRLVL,
    CLUSTR_1_CPUS_ON,
    SCHED_UPMIGRATE,
    SCHED_DOWNMIGRATE,
    SCHED_MOSTLY_IDLE_FREQ,
    IRQ_BALANCER,
    INTERACTIVE_USE_SCHED_LOAD,
    INTERACTIVE_USE_MIGRATION_NOTIF,
    INPUT_BOOST_RESET,
    /* represents the maximum number of
     * optimizations allowed per
     * request and should always be
     * the last element
     */
    OPTIMIZATIONS_MAX
};

int mpctl_send(int control /* MPCTL_CMD_* */, ...);

#ifdef __cplusplus
}
#endif

#endif /* __MP_CTL_H__ */
