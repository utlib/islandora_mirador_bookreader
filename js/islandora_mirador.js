(function($) {
$(function() {

	/* Switch the Mirador view type based on the Drupal setting */
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

	/* Setup the base URL for windowObjects or data attribute to render */
	var pid = Drupal.settings.islandora_mirador_bookreader.pid;
	var base_url = Drupal.settings.islandora_mirador_bookreader.base_url;
	var manifest_datastream = Drupal.settings.islandora_mirador_bookreader.manifest_datastream;
	var manifest_url = base_url + "/islandora/object/" + pid + "/datastream/" + manifest_datastream + "/view";	

	/* Retrieve the JSON array of links to manifests, if any, and supply it to Mirador's constructor */
	var manifest_list_url = Drupal.settings.islandora_mirador_bookreader.manifest_list_url;
	if (!manifest_list_url) {

		Mirador({
			"id": "mirador-bookreader",
			"data":[{ "manifestUri": manifest_url, "location": "University of Toronto"}],
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
                                }
			]		
		});

	} else {

		$.getJSON(manifest_list_url, function(data) {
			/* Verify that the JSON retrieved is indeed array */
			if (Object.prototype.toString.call(data) != '[object Array]') {
				throw 'TypeError: Manifest list retrieved via Drupal manifest list URL is not an JSON array';
			}
	
			/* Move the current page's manifest to the top of the manifest list, so the bookreader loads it first while loading the others in the background afterwards */	
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
					}
				]
			});
		});
	};
});

})(jQuery);
