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

	// The manifest_url is dynamically generated based on the pid
	var pid = Drupal.settings.islandora_mirador_bookreader.pid;
	var manifest_url = "https://paleographydev.library.utoronto.ca/islandora/object/" + pid + "/datastream/SC/";	

	// This is the main Mirador constructor. The settings corresponds to settings.js in the source code, see there for more help
      Mirador({
        "id": "mirador-bookreader",
        "data": [ 
        	{
			"manifestUri": manifest_url, "location": "University of Toronto"
	        	//"manifestUri": "https://paleographydev.library.utoronto.ca/sites/paleographydev.library.utoronto.ca/files/js/toronto.json", "location": "University of Toronto"
		}
        ],
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

	'logosPath' : '/sites/all/libraries/mirador/logos/',
	
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
	
	// Mirador loads its own jQuery version (1.9.1). We need to raise Drupal's jQuery version using the migrate library, if Drupal's behind
	$.getScript("https://code.jquery.com/jquery-migrate-1.2.1.js");
});

function scrollToMetadata() {
	$('html, body').animate({
		scrollTop: $('.islandora-metadata').offset().top
	}, 1000);	
}
