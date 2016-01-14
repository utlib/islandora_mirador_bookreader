# Islandora Mirador Bookreader

## Introduction

This module makes use of the [Mirador](https://github.com/IIIF/mirador) open source viewer for Islandora Book Objects (replacing the Islandora Internet Archives Bookreader). This module requires that you have a IIIF image server installed. This module development was supported by the The Andrew W. Mellon Foundation for the [French Renaissance Paleography website] (https://paleography.library.utoronto.ca/).

## Prerequisites

* Drupal module [libraries](https://www.drupal.org/project/libraries)
* Compiled Mirador javascript library
[Stable 2.0 version](https://github.com/IIIF/mirador/releases)
[Sourcecode on Github](http://iiif.github.io/mirador/) The master branch contains many new features that you can try

### IIIF server and manifest generation

This bookreader relies on two other components:

* An image server that complies with the IIIF Image API 2.0 specified [here](http://iiif.io/api/image/2.0/).
* An Shared Canvas Manifest datastream generated for each Book object, specified in the IIIF Presentation API 2.0 [here](http://iiif.io/api/presentation/2.0/#primary-resource-types)

[Loris](https://github.com/loris-imageserver/loris) can be used for the image server.

## Install

1. As usual, download or clone this repo into Drupal's module directory and enable.
2. Download the Mirador compiled javascript library, unzip, and place into "sites/all/libraries" as with other libraries.
3. Choose "Mirador Bookreader" in the list of viewers on the Book Solution Pack configuration page - http://path.to.your.site/admin/islandora/solution_pack_config/book
4. [Optional] On the Book Solution Pack configuration page in step #3, you can click on "configure" to reach the Mirador configuration page at http://path.to.your.siteadmin/islandora/islandora_viewers/mirador_bookreader. Here you can select the "Default page view" (i.e. (Image, Book, Thumbnails) and also enter the PID of the parent collection containing the book objects that you want to display in your site's Mirador BookReader - i.e. "islandora:root". This will generate the manifest list URL in the Mirador Bookreader configuration page in Drupal.

## Configure

Most configurations are pure Mirador javascript parameters when initializing, not Drupal. These parameters are documentated on Mirador's Github wiki. The parameters are set in this module's "js/islandora_mirador.js" file.

## Known issues

* The thumbnails do not appear unless the view changes. This is due to mirador.js not putting the link to the image inside the "src" attribute in its HTML image tag. Modification to mirador.js is needed to fix this. 

## Maintainers

* [University of Toronto Libraries](https://github.com/utlib)

