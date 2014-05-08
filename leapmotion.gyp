{
    'targets': [
        {
            'target_name': 'leapmotion',
            'type': 'shared_library',
            'msvs_guid': 'C01554BF-E298-4BF3-A257-5D4675D2A8E9',
            'dependencies': ['<(jsx)/sdk/core/core.gyp:core'],
            'direct_dependent_settings': {
                'include_dirs': ['src'],
            },
            'defines': ['LEAPMOTION_EXPORTS'],
            'sources': [
                'src/leapmotion.cpp',
                'src/leapmotion.hpp',
                'src/leapmotion_core.cpp',
                'src/leapmotion_core.hpp',
            ],
            'conditions': [
                ['OS=="win"', {
                    "configurations": {
                        "Debug": {
                            "msvs_settings": {
                                "VCLinkerTool": {
                                    "AdditionalLibraryDirectories": [
                                        "./LeapSDK/lib/x86"
                                    ]
                                }
                            }
                        },                
                        "Release": {
                            "msvs_settings": {
                                "VCLinkerTool": {
                                    "AdditionalLibraryDirectories": [
                                        "./LeapSDK/lib/x86"
                                    ]
                                }
                            }
                        },                
                    },
                    "link_settings": {
                            "libraries": [
                                "-lleap.lib",
                            ]
                        },
                    'sources': [
                    ],
                }],
                ['OS=="linux"', {
                    'sources': [
                    ],
                }],
            ],
        },
    ],
}