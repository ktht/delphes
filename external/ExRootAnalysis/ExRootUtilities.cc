
/** \class ExRootUtilities
 *
 *  Functions simplifying ROOT tree analysis
 *
 *  \author P. Demin - UCL, Louvain-la-Neuve
 *
 */

#include "ExRootAnalysis/ExRootUtilities.h"

#include "TChain.h"
#include "TH1.h"
#include "TROOT.h"

#include <fstream>
#include <iostream>
#include <filesystem>

using namespace std;

static const Font_t kExRootFont = 42;
static const Float_t kExRootFontSize = 0.04;

void HistStyle(TH1 *hist, Bool_t stats)
{
  hist->SetLineWidth(2);
  hist->SetLineColor(kBlack);
  hist->SetMarkerStyle(kFullSquare);
  hist->SetMarkerColor(kBlack);

  hist->GetXaxis()->SetTitleOffset(1.5);
  hist->GetYaxis()->SetTitleOffset(1.75);
  hist->GetZaxis()->SetTitleOffset(1.5);

  hist->GetXaxis()->SetTitleFont(kExRootFont);
  hist->GetYaxis()->SetTitleFont(kExRootFont);
  hist->GetZaxis()->SetTitleFont(kExRootFont);
  hist->GetXaxis()->SetTitleSize(kExRootFontSize);
  hist->GetYaxis()->SetTitleSize(kExRootFontSize);
  hist->GetZaxis()->SetTitleSize(kExRootFontSize);

  hist->GetXaxis()->SetLabelFont(kExRootFont);
  hist->GetYaxis()->SetLabelFont(kExRootFont);
  hist->GetZaxis()->SetLabelFont(kExRootFont);
  hist->GetXaxis()->SetLabelSize(kExRootFontSize);
  hist->GetYaxis()->SetLabelSize(kExRootFontSize);
  hist->GetZaxis()->SetLabelSize(kExRootFontSize);

  hist->SetStats(stats);
}

//------------------------------------------------------------------------------

Bool_t FillChain(TChain *chain, const char *inputFileList)
{
  ifstream infile(inputFileList);
  string buffer;

  if(!infile.is_open())
  {
    cerr << "** ERROR: Can't open '" << inputFileList << "' for input" << endl;
    return kFALSE;
  }

  while(1)
  {
    infile >> buffer;
    if(!infile.good()) break;
    chain->Add(buffer.c_str());
  }

  return kTRUE;
}

//------------------------------------------------------------------------------

std::string FindInput(const char * fileName,
                      const std::string & env_name)
{
  const std::string fileNameStr = fileName;
  if(! fileNameStr.empty())
  {
    if(! std::filesystem::exists(fileNameStr))
    {
      if(const char * search_env = std::getenv(env_name.data()))
      {
        const std::filesystem::path candidate_file(fileNameStr);
        std::istringstream ss(search_env);
        std::string search_path;
        while(std::getline(ss, search_path, ':'))
        {
          const std::filesystem::path candidate_dir(search_path);
          const std::filesystem::path candidate_path = candidate_dir / candidate_file;
          if(std::filesystem::exists(candidate_path))
          {
            return candidate_path.string();
          }
        }
      }
    }
  }
  return fileNameStr;
}

//------------------------------------------------------------------------------
