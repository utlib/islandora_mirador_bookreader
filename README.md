# Islandora Mirador Bookreader

## Introduction

This module makes use of the [Mirador](https://github.com/IIIF/mirador) open source viewer for Islandora Book Objects (replacing the Islandora Internet Archives Bookreader). This module requires that you have a IIIF image server installed. This module development was supported by the The Andrew W. Mellon Foundation for the [French Renaissance Paleography website] (https://paleography.library.utoronto.ca/).

## Prerequisites

* Drupal module [libraries](https://www.drupal.org/project/libraries)
* Compiled Mirador javascript library
  * [Stable 2.0 version](https://github.com/IIIF/mirador/releases)
  * [Sourcecode on Github](http://iiif.github.io/mirador/) The master branch contains many new features that you can try
* An image server that complies with the IIIF Image API 2.0 specified [here](http://iiif.io/api/image/2.0/).
  * [Loris](https://github.com/loris-imageserver/loris) can be used for the image server.
* An Shared Canvas Manifest datastream generated for each Book object, specified in the IIIF Presentation API 2.0 [here](http://iiif.io/api/presentation/2.0/#primary-resource-types)
  * The [Islandora SC Manifest module](https://github.com/utlib/islandora_sc_manifest) can generate them.

## Installation

1. Put the compiled Mirador library under `sites/all/libraries`
2. Download and enable the reader module.

At this point, the reader will show an example manuscript with an option to manually add SharedCanvas Manifests from URL.
However, the reader can automatically load the current object's manifest, give that you have set up an IIIF image server and generated the necessary manifests. If you have done those steps, continue with the steps below:
1. Open Mirador Bookreader configuration `admin/islandora/islandora_viewers/mirador_bookreader`
2. Under **Manfiest datastream ID** enter the correct value. If you are using Islandora SC Manifest module, the default ID is **SC**.

## Configure

Most configurations are pure Mirador javascript parameters when initializing, not Drupal. These parameters are documentated on Mirador's Github wiki. The parameters are set in this module's "js/islandora_mirador.js" file.

## Known issues

* The thumbnails do not appear unless the view changes. This is due to mirador.js not putting the link to the image inside the "src" attribute in its HTML image tag. Modification to mirador.js is needed to fix this. 

## Maintainers

* [University of Toronto Libraries](https://github.com/utlib)

