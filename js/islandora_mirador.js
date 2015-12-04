$(function() {
	// This view type corresponds with the Drupal module setting
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
	//console.log("The view type from config is " + view_type + " <<<<");

	var json_path = Drupal.settings.islandora_mirador_bookreader.json_file_directory+'sc_manifest_list.json';

	$.getJSON(json_path, function(data) {

	// The manifest_url is dynamically generated based on the pid
	var pid = Drupal.settings.islandora_mirador_bookreader.pid;

	var base_url = Drupal.settings.islandora_mirador_bookreader.base_url;

	//put a base url
	var manifest_url = base_url + "/islandora/object/" + pid + "/datastream/SC/";	

	// This is the main Mirador constructor. The settings corresponds to settings.js in the source code, see there for more help
      Mirador({
        "id": "mirador-bookreader",
        "data": data,
	'mainMenuSettings': {
		'show':false,
		'buttons':{
			'bookmark' : false
		}
	},
	"showAddFromURLBox":false,	

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
			"viewType":view_type,
			"annotationLayer":false,
			"displayLayout": true,
			"bottomPanel" : true,
			"sidePanel" : false,
			//"overlay": false,
			"overlayMetadata": false,
		}
	]
      });
	});

});

function scrollToMetadata() {
	$('html, body').animate({
		scrollTop: $('.islandora-metadata').offset().top
	}, 1000);	
}
