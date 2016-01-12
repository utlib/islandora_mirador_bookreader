# Islandora Mirador Bookreader

## Introduction

Using the [Mirador](https://github.com/IIIF/mirador) open-source image viewer, this module is designed to implement IIIF compliant on drupal islandora environment.

## Prerequisites

* [Libraries](https://www.drupal.org/project/libraries)
* [Mirador](http://iiif.github.io/mirador/)

## Install

1. As usual, download or clone this repo into Drupal's module directory and enable.
2. Download the Mirador compiled javascript library, unzip, and place into "sites/all/libraries" as with other libraries.
3. Choose "Mirador Bookreader" in the list of viewers on the Book Solution Pack configuration page. 
4. [Optional] On the list of viewers page in step #3, click on "configure" for Mirador and Enter the manifest list URL in the Mirador Bookreader configuration page in Drupal.

## Configure

Most configurations are pure Mirador javascript parameters when initializing, not Drupal. These parameters are documentated on Mirador's Github wiki. The parameters are set in this module's "js/islandora_mirador.js" file.

The only Drupal configuration so far is the dropdown selection of "viewType". This can be found through the usual Islandora module configuration pages.

## Maintainers

* [University of Toronto Libraries](https://github.com/utlib)

