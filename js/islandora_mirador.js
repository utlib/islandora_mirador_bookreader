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

	var manifest_url = Drupal.settings.islandora_mirador_bookreader.manifest_url;
	console.log("Manifest URL: ", manifest_url);

	function getSelectedCanvasID() {

		// Returns full URL
		var url = window.location.href;
		// Check if the url has #page/number
		var res = url.match(/#page\/\d*[0-9]\d*/g);
		var selected_canvasID = '';

		// If #page/number exists,
		// we want to open the page in Mirador viewer
		if(res !== null) {
			var pageSequence = '';
			$.each(res, function(key, value) {
				pageSequence = Number(value.replace("#page/", ""));
			});

		    $.getJSON(manifest_url, function(result){
		        $.each(result.sequences[0].canvases, function(i, field){
					if(i == pageSequence-1) {
						selected_canvasID = field["@id"];
						setMiradorConstructor(selected_canvasID);
					}
		       });
		    });
		} else {
			setMiradorConstructor(selected_canvasID);
		}
	}


	function setMiradorConstructor(selected_canvasID) {

		/* Retrieve the JSON array of links to manifests, if any, and supply it to Mirador's constructor */
		var manifest_list_url = Drupal.settings.islandora_mirador_bookreader.manifest_list_url;
		if (!manifest_list_url) {

			Mirador({
				"id": "mirador-bookreader",
				"data":[{ "manifestUri": manifest_url, "location": "University of Toronto"}],
				'buildPath' : '/sites/all/libraries/mirador/',
				'i18nPath' : 'locales/',
				'imagesPath' : 'images/',
				'logosPath' : 'images/logos/',
				'logosLocation' : 'logos/',
				'repoImages' : {
					'other': 'iiif_logo.png'
				},
				"windowObjects": [
					{
						"loadedManifest":manifest_url,
						"canvasID" : selected_canvasID, 
						"viewType":view_type
					}
				]		
			});

		} else {

			$.getJSON(manifest_list_url, function(data) {
				/* Verify that the JSON retrieved is indeed array. More error checking should be added later */
				if (Object.prototype.toString.call(data) != '[object Array]') {
					throw 'TypeError: Manifest list retrieved via Drupal manifest list URL is not an JSON array';
				}
		
				/* Move the current page's manifest to the top of the manifest list, so the bookreader loads it first then loads the others in the background */	
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
					'i18nPath' : 'locales/',
					'imagesPath' : 'images/',
					'logosPath' : 'images/logos/',
					'logosLocation' : 'logos/',
					'repoImages' : {
						'other': 'iiif_logo.png'
					},
					"windowObjects": [
						{
							"loadedManifest":manifest_url,
							"viewType":view_type
						}
					]
				});
			});
		}

	}

	getSelectedCanvasID();

});

})(jQuery);


// Make "i" icon (info button) in Mirador viewer toggle to 
// metadata details below
function scrollToMetadata() {
        jQuery('html, body').animate({
                scrollTop: jQuery('.islandora-metadata').offset().top
        }, 1000);
}