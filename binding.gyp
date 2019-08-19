{
	"targets": [
		{
			"target_name": "vjoy",
			"sources": [ "src/vjoy.cpp" ],
			"include_dirs": [
				"<(module_root_dir)/include",
			],
			"libraries": [
				"<(module_root_dir)/native/<(target_arch)/vJoyInterface.lib"
			],
			"copies": [
				{
					"destination": "<(module_root_dir)/build/Release/",
					"files": [ "<(module_root_dir)/native/<(target_arch)/vJoyInterface.dll" ]
				}
			]
		}
	],
}