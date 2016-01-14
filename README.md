# Islandora Mirador Bookreader

## Introduction

This module makes use of the [Mirador](https://github.com/IIIF/mirador) open source viewer for Islandora Book Objects (replacing the Islandora Internet Archives Bookreader). This module requires that you have a IIIF image server installed.

## Prerequisites

* [Libraries](https://www.drupal.org/project/libraries)
* [Mirador](http://iiif.github.io/mirador/)

## Install

1. As usual, download or clone this repo into Drupal's module directory and enable.
2. Download the Mirador compiled javascript library, unzip, and place into "sites/all/libraries" as with other libraries.
3. Choose "Mirador Bookreader" in the list of viewers on the Book Solution Pack configuration page - http://path.to.your.site/admin/islandora/solution_pack_config/book
4. [Optional] On the Book Solution Pack configuration page in step #3, you can click on "configure" to reach the Mirador configuration page at http://path.to.your.siteadmin/islandora/islandora_viewers/mirador_bookreader. Here you can select the "Default page view" (i.e. (Image, Book, Thumbnails) and also enter the PID of the parent collection containing the book objects that you want to display in your site's Mirador BookReader - i.e. "islandora:root". This will generate the manifest list URL in the Mirador Bookreader configuration page in Drupal.

## Configure

Most configurations are pure Mirador javascript parameters when initializing, not Drupal. These parameters are documentated on Mirador's Github wiki. The parameters are set in this module's "js/islandora_mirador.js" file.

The only Drupal configuration so far is the dropdown selection of "viewType". This can be found through the usual Islandora module configuration pages.

## Maintainers

* [University of Toronto Libraries](https://github.com/utlib)

