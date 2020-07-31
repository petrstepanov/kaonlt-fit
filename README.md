# KaonTL Fit

A CERN ROOT based C++ program used for the Kaon LT prototype PMT spectra fitting.

<figure>
  <img src="https://raw.githubusercontent.com/petrstepanov/kaonlt-fit/master/resources/kaonlt-fit-diagram.png" alt="Diagram of the KaonLT Fit application"style="width: 100%">
 <figcaption>Diagram of the KaonLT Fit application.</figcaption>
</figure> 

Program opens a set of files specified as command line arguments. Class `Constants` parses command line arguments. 

Class `TreeHelper` opens each ROOT file and imports the ROOT Tree. Tree name is provided in in `--tree-name=tree1;3 ` command line parameter. The tree contains data from two PMTs. Namely, `tile`, `channel` and `amplitude` and has following structure:

        ************************************************************************************
        *    Row   *     tilel *     tiler *     amp_1 *     amp_2 *      ch_1 *      ch_2 *
        ************************************************************************************
        *        0 *        77 *        93 *         0 *         0 *         0 *         0 *
        *        1 *        75 *        29 *         0 *         0 *         0 *         0 *
        *        2 *       126 *        87 *         0 *         0 *         0 *         0 *
        *      ... *       ... *       ... *       ... *       ... *       ... *       ... *

Optional parameter `--plot-tree=kFALSE` controls whether the original Tree data is plotted. When set to `kTRUE`, program generates 2D histograms with the original Tree data and saves them to the hard drive. These plots look as follows:

<img src="https://raw.githubusercontent.com/petrstepanov/kaonlt-fit/master/resources/tree1;3-ch:tile-amp:tile.png" style="width: 100%">

Program constructs one-dimensional projections for each PMT histogram at the value of Tile (`tilel` for PMT1 and `tiler` for PMT2) equal to a certain value. This threshold value is spacified in the `--tile-profile=55` command line argument. An extra condition is added for selection of the data for the projections. Only events with non-zero Tile pairs are considered (`tilel!=0 && tiler!=0`). This provies more clean experimental data. We make sure that there is a hit in each PMT.

Following projections for PMT histograms are obtained:

<img src="https://raw.githubusercontent.com/petrstepanov/kaonlt-fit/master/resources/pmtsCanvas.png" style="width: 100%">

Next the PMT spectra are fit in order to determine the number of the photoelectrons.
