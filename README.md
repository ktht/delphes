[![CI](https://github.com/delphes/delphes/actions/workflows/ci.yml/badge.svg)](https://github.com/delphes/delphes/actions/workflows/ci.yml) [![DOI](https://zenodo.org/badge/21390046.svg)](https://zenodo.org/badge/latestdoi/21390046)

Delphes
=======

Delphes is a C++ framework, performing a fast multipurpose detector response simulation.

More details can be found on the Delphes website http://cp3.irmp.ucl.ac.be/projects/delphes

Changes wrt upstream
====================

The following changes have been implemented wrt 3.5.0 version of upstream:

* average number of PU interactions is reduced from 50 to 32, corresponding to 69.2 mb minimum bias cross section in 2017 and 2018 data-taking period (see [here](https://twiki.cern.ch/twiki/bin/view/CMSPublic/LumiPublicResults));
* jet cone radius decreased from 0.5 to 0.4;
* save the actual event number, not the entry number to the `Event.Number` branch;
* save all information pulled from `GenEventInfoProduct`;
* technical changes which allow to run `DelphesCMSFWLite` anywhere (not just in the root directory of this repository).

Running in CMSSW
================

Set up your environment

```bash
source /cvmfs/cms.cern.ch/cmsset_default.sh
cmsrel CMSSW_11_1_2 # need gcc 8
cd $_/src
cmsenv
```

Set up Delphes

```bash
cd $HOME/somedirectory
git clone --depth 1 --branch 3.5.0 git@github.com:ktht/delphes.git
cd delphes
./configure
make clean && make distclean # for cleaning
make -j8 # build
source ./set_env.sh
```

Run (anywhere):

```bash
DelphesCMSFWLite delphes_card_CMS_PileUp.tcl output.root input.root
```
`input.root` can be any ROOT file in CMS data tier format that stores `std::vector<reco::GenParticle>` (and possibly `std::vector<pat::PackedGenParticle>`), such as `GEN`, `GEN-SIM`, `AODSIM` or `MINIAODSIM`.
The `DelphesCMSFWLite` command can be cancelled at any time.
Whatever has been processed during the execution will be saved to an Ntuple called `output.root`.
For more information about PU simulation, see [these slides](https://indico.cern.ch/event/873524/contributions/3697290/attachments/1988392/3315700/Korea_DetectorSimulation2.pdf).

In order to produce a flat tree from `output.root`, visit: https://github.com/ktht/DelphesNtuplizer

Quick start with Delphes
========================

Commands to get the code:

```
   wget http://cp3.irmp.ucl.ac.be/downloads/Delphes-3.5.0.tar.gz

   tar -zxf Delphes-3.5.0.tar.gz
```

Commands to compile the code:

```
   cd Delphes-3.5.0

   make
```

Finally, we can run Delphes:

```
   ./DelphesHepMC3
```

Command line parameters:

```
   ./DelphesHepMC3 config_file output_file [input_file(s)]
     config_file - configuration file in Tcl format
     output_file - output file in ROOT format,
     input_file(s) - input file(s) in HepMC format,
     with no input_file, or when input_file is -, read standard input.
```

Let's simulate some Z->ee events:

```
   wget http://cp3.irmp.ucl.ac.be/downloads/z_ee.hep.gz
   gunzip z_ee.hep.gz
   ./DelphesSTDHEP cards/delphes_card_CMS.tcl delphes_output.root z_ee.hep
```

or

```
   curl -s http://cp3.irmp.ucl.ac.be/downloads/z_ee.hep.gz | gunzip | ./DelphesSTDHEP cards/delphes_card_CMS.tcl delphes_output.root
```

For more detailed documentation, please visit https://cp3.irmp.ucl.ac.be/projects/delphes/wiki/WorkBook

Configure Delphes on lxplus.cern.ch
====================================

```
git clone git://github.com/delphes/delphes.git Delphes

cd Delphes

source /cvmfs/sft.cern.ch/lcg/views/LCG_99/x86_64-centos7-gcc10-opt/setup.sh

make 
```

Simple analysis using TTree::Draw
=================================

Now we can start [ROOT](root.cern) and look at the data stored in the output ROOT file.

Start ROOT and load Delphes shared library:

```
   root -l
   gSystem->Load("libDelphes");
```

Open ROOT file and do some basic analysis using Draw or TBrowser:

```
   TFile *f = TFile::Open("delphes_output.root");
   f->Get("Delphes")->Draw("Electron.PT");
   TBrowser browser;
```

Notes:
* ```Delphes``` is the tree name. It can be learned e.g. from TBrowser.
* ```Electron```is the branch name; ```PT``` is a variable (leaf) of this branch.

Complete description of all branches can be found in [doc/RootTreeDescription.html](doc/RootTreeDescription.html).
This information is also available [in the workbook](https://cp3.irmp.ucl.ac.be/projects/delphes/wiki/WorkBook/RootTreeDescription).

Macro-based analysis
====================

Analysis macro consists of histogram booking, event loop (histogram filling),
histogram display.

Start ROOT and load Delphes shared library:

```
   root -l
   gSystem->Load("libDelphes");
```

Basic analysis macro:

```
{
  // Create chain of root trees
  TChain chain("Delphes");
  chain.Add("delphes_output.root");
  
  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();
  
  // Get pointers to branches used in this analysis
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");

  // Book histograms
  TH1 *histElectronPT = new TH1F("electron pt", "electron P_{T}", 50, 0.0, 100.0);

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {

    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);
  
    // If event contains at least 1 electron
    if(branchElectron->GetEntries() > 0)
    {
      // Take first electron
      Electron *electron = (Electron*) branchElectron->At(0);
      
      // Plot electron transverse momentum
      histElectronPT->Fill(electron->PT);
      
      // Print electron transverse momentum
      cout << electron->PT << endl;
    }

  }

  // Show resulting histograms
  histElectronPT->Draw();
}
```

More advanced macro-based analysis
==================================

The 'examples' directory contains ROOT macros [Example1.C](examples/Example1.C), [Example2.C](examples/Example2.C) and [Example3.C](examples/Example3.C).

Here are the commands to run these ROOT macros:

```
   root -l
   .X examples/Example1.C("delphes_output.root");
```

or

```
   root -l examples/Example1.C'("delphes_output.root")'
```
