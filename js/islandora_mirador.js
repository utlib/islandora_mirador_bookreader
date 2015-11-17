$(function() {
	var pid = Drupal.settings.islandora_mirador_bookreader.pid;
	console.log(">>>>" + pid + "<<<<");
	var manifest_url = "https://sz-paleographydev.library.utoronto.ca/islandora/object/" + pid + "/datastream/SC/";	
	console.log(manifest_url);

      Mirador({
        "id": "mirador-bookreader", // The CSS ID selector for the containing element.
        "layout": "1x1", // The number and arrangement of windows ("row"x"column")?
        "data": [ 
        // This array holds the manifest URIs for the IIIF resources you want Mirador to make available to the user.
        // Each manifest object must have a manifest URI pointing to a valid IIIF manifest, and may also
        // provide a location to be displayed in the listing of available manifests.
        { "manifestUri": manifest_url, "location": "University of Toronto"}
        //{ "manifestUri": "https://sz-paleographydev.library.utoronto.ca/sites/sz-paleographydev.library.utoronto.ca/files/json/toronto.json", "location": "University of Toronto"}
        ],
        // This array allows the user to specify which of the included manifests should appear 
        // in the workspace, and what the configuration of the window (zoom level, open panels, etc.) 
        // ought to be. To begin with, we will leave it blank. 
	'mainMenuSettings': {
              'buttons' : {
                'bookmark' : false
              }
        },
	"showAddFromURLBox":false,	
        "windowObjects": [
		{
			"loadedManifest":manifest_url,
			"viewType":"ImageView",
			"annotationLayer":false
		}
	]
      });
    });
