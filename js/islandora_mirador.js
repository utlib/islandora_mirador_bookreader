$(function() {
	var pid = Drupal.settings.islandora_mirador_bookreader.pid;
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
	var manifest_url = "https://paleographydev.library.utoronto.ca/islandora/object/" + pid + "/datastream/SC/";	

      Mirador({
        "id": "mirador-bookreader", // The CSS ID selector for the containing element.
        //"layout": "1x1", // The number and arrangement of windows ("row"x"column")?	
        "data": [ 
        // This array holds the manifest URIs for the IIIF resources you want Mirador to make available to the user.
        // Each manifest object must have a manifest URI pointing to a valid IIIF manifest, and may also
        // provide a location to be displayed in the listing of available manifests.
        { "manifestUri": manifest_url, "location": "University of Toronto"}
        //{ "manifestUri": "https://sz-paleographydev.library.utoronto.ca/sites/sz-paleographydev.library.utoronto.ca/files/json/toronto.json", "location": "University of Toronto"}
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
			"displayLayout": false,
			"bottomPanel" : true,
			"sidePanel" : false
		}
	]
      });
	
	$.getScript("https://code.jquery.com/jquery-migrate-1.2.1.js");
});
