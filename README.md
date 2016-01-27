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

## Customizations for the French Renaissance Paleography website

### Bryan Haberberger's version of Mirador javascript library
Paleography does not use the default Mirador javascript library, instead, uses a modified version by [Bryan Haberberger](https://github.com/thehabes) from Saint Louis University.
This version is a fork of the official version 2.0 library, and includes image manipulation in the UI, improved error catching and other improvements. This version is actively maintained by Bryan.

### Fixed thumbnail not showing up on first load
The thumbnails do not appear unless the view changes. In $.ThumbnailsView's Handelbars the src attribute does not receive the value when first loading.
To fix this, thumbUrl was placed into the src value.

### Load current manuscript first
When Mirador is initialized with an array of manifests, it can display any one of them automatically by setting the loadedManifest option in the windowObjects array. However, Mirador does not prioritize loading the loadedManifest, causing it to wait until the other manifests before it in the array have been loaded. If the current manifest is in low position in a large array, the wait could be long.
The fix was to manually rearrange the loadedManifest's position to be at top before initializing Mirador.

### Removing annotation overlay from all windows
In official release the annotation overlay "speech bubble" can be removed by setting annotationLayer to false in the windowObjects array. However, the setting could not be applied to subsequent windows. Instead, the overlay link is hidden from view via CSS.

## Current maintainers

* [University of Toronto Libraries:](http://its.library.utoronto.ca/)
	* [Kelli Babcock](http://its.library.utoronto.ca/staff/kelli-babcock)
	* [Sunny Lee](https://github.com/sunnywd)
	* [Sean Xiao Zhao](https://github.com/sean-xiao-zhao7)
	* [Bilal Khalid](https://github.com/bilalkhalid)
	* [Chulhee Yoon](https://github.com/cyoon84)
	* [Gordon Belray](https://gordonbelray.com)

