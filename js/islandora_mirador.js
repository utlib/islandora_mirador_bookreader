(function($) {
$(function() {
	var view_type = Drupal.settings.islandora_mirador_bookreader.view_type;	
	switch(parseInt(view_type)) {
		case 1:
			view_type = "ImageView";
			break;
		case 2:	
			view_type = "BookView";
			break;	
		case 3:
			view_type = "ThumbnailsView";
			break;
		default:
			view_type = "ImageView";
	}

	var manifest_list_url = Drupal.settings.islandora_mirador_bookreader.manifest_list_url;
	if (!manifest_list_url) {
		manifest_list_url = Drupal.settings.islandora_mirador_bookreader.json_file_directory+'sc_manifest_list.json';
	}

	$.getJSON(manifest_list_url, function(data) {

		// Retrieves the current object's PID and uses it to construct the URL for Mirador's windowObjects' loadedManifest attribute 
		var pid = Drupal.settings.islandora_mirador_bookreader.pid;
		var base_url = Drupal.settings.islandora_mirador_bookreader.base_url;
		var manifest_url = base_url + "/islandora/object/" + pid + "/datastream/SC/view";
			
		// Grab the current object and put it into the beginning of the array
		// This is to make the Mirador viewer load faster
		var new_data = []; 
		$.each(data, function(idx, obj) {
			if (obj.manifestUri == manifest_url) {
				new_data.unshift(obj); 
			} else {
				new_data.push(obj); 
			}
		});

		Mirador({
			"id": "mirador-bookreader",
			"data": new_data,
			
			/* Optional parameters
			"data":[{ "manifestUri": manifest_url, "location": "University of Toronto"}],
			'mainMenuSettings': {
				'show':false,
				'buttons': { 'bookmark' : false }
			},
			"showAddFromURLBox":false,	
			*/

			'buildPath' : '/sites/all/libraries/mirador/',

			'i18nPath' : '/sites/all/libraries/mirador/locales/',

			'imagesPath' : '/sites/all/libraries/mirador/images/',

			'logosPath' : '/sites/all/libraries/mirador/images/logos/',

			'logosLocation' : '/sites/all/libraries/mirador/images/logos/',

			'repoImages' : {
				'other': 'iiif_logo.png'
			},

			"windowObjects": [
				{
					"loadedManifest":manifest_url,
					"viewType":view_type
					/*
					"annotationLayer":false,
					"displayLayout": true,
					"bottomPanel" : true,
					"sidePanel" : false,
					"overlayMetadata": false
					*/
				}
			]
		});
	}); //getJSON
});

})(jQuery);
