{
	"targets": [
		{
			"target_name": "vjoy",
			"sources": [ 
				"src/utils.cpp", 
				"src/general.cpp", 
				"src/device.cpp", 
				"src/feeding.cpp", 
				"src/vjoy.cpp" 
			],
			"include_dirs": [
				"<(module_root_dir)/include",
				"<!@(node -p \"require('node-addon-api').include\")"
			],
			"dependencies": [
				"<!(node -p \"require('node-addon-api').gyp\")"
			],
			"libraries": [
				"<(module_root_dir)/native/<(target_arch)/vJoyInterface.lib"
			],
			"copies": [
				{
					"destination": "<(module_root_dir)/build/Release/",
					"files": [ "<(module_root_dir)/native/<(target_arch)/vJoyInterface.dll" ]
				}
			],
			"defines": [
				"NAPI_DISABLE_CPP_EXCEPTIONS"
			]
		}
	],
}