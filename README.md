# Islandora Mirador Bookreader

## Introduction

This module implements [Mirador](https://github.com/IIIF/mirador) open source [IIIF](http://iiif.io/) image viewer for [Islandora Book Solution Pack](https://github.com/Islandora/islandora_solution_pack_book). 

This module development was supported by the The Andrew W. Mellon Foundation for the [French Renaissance Paleography website] (https://paleography.library.utoronto.ca/).

## Prerequisites

* Drupal module [Libraries](https://www.drupal.org/project/libraries)
* Compiled Mirador javascript library
  * [Stable 2.0 version](https://github.com/IIIF/mirador/releases)
  * [Sourcecode on Github](http://iiif.github.io/mirador/) You need to compile it; the 2.0.0 tag is identical as the release. The Master branch contains many experimental features that are not stable, but fun for testing.
* An IIIF [Image API](http://iiif.io/api/image/2.0/) server.
  * [Loris](https://github.com/loris-imageserver/loris) works well.
* JSON [SharedCanvas Manifest](http://iiif.io/api/presentation/2.0/#manifest) Fedora datastreams for Book Solution Pack objects
  * You can generate them using the [Islandora SC Manifest module](https://github.com/utlib/islandora_sc_manifest)

## Install
1. Download compiled Mirador javascript library into Drupal's libraries directory, usually in`sites/all/libraries`. Verify the file permission is web servable. 
2. Clone and enable this module.
3. Go to admin/islandora/solution_pack_config/book` and choose **Mirador BookReader** under Book Viewers.

At this point, the viewer will show an example manuscript with an option to manually add SharedCanvas Manifests from URL.

### Generate SharedCanvas Manifest datastreams
In order for the viewer to automatically display the current page's book object, you must generate a SCManifest JSON datastream for the object and tell the viewer to use this datastream when loading the page.

Please read the instruction within the [Islandora SC Manifest module](https://github.com/utlib/islandora_sc_manifest) module or the [SharedCanvas Manifest](http://iiif.io/api/presentation/2.0/#manifest) API on how to generate such a datastream.

After you have generate the datastream, configure the viewer with the following:

1. Open Mirador Bookreader configuration `admin/islandora/islandora_viewers/mirador_bookreader`
2. Under **Manfiest datastream ID** enter the correct value. If you are using Islandora SC Manifest module, the default ID is **SC**.

### [Optional] Manifest list configuration

This module adds the functionality of loading all the children book objects under a collection within the "Add New Object" in Mirador to allow for faster switching between objects, instead of navigating using the Drupal pages. This functionality is not required for this module to display the objects. 

For this to work, first the PID of the parent collection must be specified in `admin/islandora/islandora_viewers/mirador_bookreader`

The module can then generate an JSON list of links to SCManifest datastreams at `admin/islandora/islandora_viewers/mirador_bookreader/json_generate`

The result is a JSON array of links to the SharedCanvas Manifest datastreams of Book Solution Pack object. The Mirador viewer will use AJAX to load **all** of the links upon loading of any Book object page. 

## Known issues

* The thumbnails do not appear unless the view changes. This is due to mirador.js not putting the link to the image inside the "src" attribute in its HTML image tag. Modification to mirador.js is needed to fix this. 

## Current maintainers

* [University of Toronto Libraries:](http://its.library.utoronto.ca/)
	* [Kelli Babcock](http://its.library.utoronto.ca/staff/kelli-babcock)
	* [Sunny Lee](https://github.com/sunnywd)
	* [Sean Xiao Zhao](https://github.com/sean-xiao-zhao7)
	* [Bilal Khalid](https://github.com/bilalkhalid)
	* [Chulhee Yoon](https://github.com/cyoon84)

