/**
 * Plot kinematic distributions from GENIE events.
 *
 * For GENIEv3/v2 validation comparisons.
 *
 * A. Mastbaum <mastbaum@uchicago.edu>, 2018/12/19
 */

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TMath.h"
#include "TStyle.h"
#include "NuisTree.h"
#include "distributions.h"
#include "filter.h"

int main(int argc, char* argv[]) {
  // Parse command-line arguments
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " "
              << "OUTPUT.root INPUT.root" << std::endl;
    return 0;
  }

  gStyle->SetOptStat(0);
  gStyle->SetHistLineColor(kBlack);

  std::string outfile = argv[1];
  std::string infile = argv[2];

  // Get tree from input file
  TFile *fin = new TFile(infile.c_str(),"READ");
  TTree *intree = (TTree*)fin->Get("GenericVectors__VARS");
  NuisTree nuistr(intree);

  // Define event filters
  filters::NuMode* filt_num_ccqe = new filters::NuMode(14, enums::kQE, enums::kCC);
  filters::NuMode* filt_nue_ccqe = new filters::NuMode(12, enums::kQE, enums::kCC);
  filters::NuMode* filt_num_ccmec = new filters::NuMode(14, enums::kMEC, enums::kCC);
  filters::NuMode* filt_num_ccres = new filters::NuMode(14, enums::kRes, enums::kCC);

  // Define distributions (plots)
  std::vector<Distribution*> dists = {
    // numCCQE
    new distributions::Q2("num_ccqe_q2", filt_num_ccqe),
    new distributions::Q0Q3("num_ccqe_q0q3", filt_num_ccqe),
    new distributions::LeadPKEQ0("num_ccqe_pkeq0", filt_num_ccqe),
    new distributions::W("num_ccqe_w", filt_num_ccqe),
    new distributions::BjorkenX("num_ccqe_bjorkenx", filt_num_ccqe),
    new distributions::InelasticityY("num_ccqe_inely", filt_num_ccqe),
    new distributions::PLep("num_ccqe_plep", filt_num_ccqe),
    new distributions::ThetaLep("num_ccqe_tlep", filt_num_ccqe),
    new distributions::PThetaLep("num_ccqe_ptlep", filt_num_ccqe),
    new distributions::PPLead("num_ccqe_pp", filt_num_ccqe),
    new distributions::ThetaPLead("num_ccqe_tp", filt_num_ccqe),
    new distributions::ThetaPLead("num_ccqe_tp_40MeV", filt_num_ccqe, 0.04),
    new distributions::ThetaLepPLead("num_ccqe_tlepp", filt_num_ccqe),
    new distributions::ThetaLepPLead("num_ccqe_tlepp_40MeV", filt_num_ccqe, 0.04),
    new distributions::dPhiLepPLead("num_ccqe_dphilp", filt_num_ccqe),
    new distributions::dPhiLepPLead("num_ccqe_dphilp_40MeV", filt_num_ccqe, 0.04),
    new distributions::Mult("num_ccqe_multp", filt_num_ccqe, 2212),
    new distributions::Mult("num_ccqe_multp_30MeV", filt_num_ccqe, 2212, 0.03),
    new distributions::Mult("num_ccqe_multn", filt_num_ccqe, 2112),
    new distributions::Mult("num_ccqe_multpip", filt_num_ccqe, 211),
    new distributions::Mult("num_ccqe_multpim", filt_num_ccqe, -211),
    new distributions::Mult("num_ccqe_multpi0", filt_num_ccqe, 111),
    new distributions::Mult("num_ccqe_multkp", filt_num_ccqe, 321),
    new distributions::Mult("num_ccqe_multkm", filt_num_ccqe, -321),
    new distributions::Mult("num_ccqe_multk0", filt_num_ccqe, 311),

    // nueCCQE
    new distributions::Q2("nue_ccqe_q2", filt_nue_ccqe),
    new distributions::Q0Q3("nue_ccqe_q0q3", filt_nue_ccqe),
    new distributions::ECons("nue_ccqe_econs", filt_nue_ccqe),
    new distributions::LeadPKEQ0("nue_ccqe_pkeq0", filt_nue_ccqe),
    new distributions::W("nue_ccqe_w", filt_nue_ccqe),
    new distributions::BjorkenX("nue_ccqe_bjorkenx", filt_nue_ccqe),
    new distributions::InelasticityY("nue_ccqe_inely", filt_nue_ccqe),
    new distributions::PLep("nue_ccqe_plep", filt_nue_ccqe),
    new distributions::ThetaLep("nue_ccqe_tlep", filt_nue_ccqe),
    new distributions::PThetaLep("nue_ccqe_ptlep", filt_nue_ccqe),
    new distributions::PPLead("nue_ccqe_pp", filt_nue_ccqe),
    new distributions::ThetaPLead("nue_ccqe_tp", filt_nue_ccqe),
    new distributions::ThetaPLead("nue_ccqe_tp_40MeV", filt_nue_ccqe, 0.04),
    new distributions::ThetaLepPLead("nue_ccqe_tlepp", filt_nue_ccqe),
    new distributions::ThetaLepPLead("nue_ccqe_tlepp_40MeV", filt_nue_ccqe, 0.04),
    new distributions::dPhiLepPLead("nue_ccqe_dphilp", filt_nue_ccqe),
    new distributions::dPhiLepPLead("nue_ccqe_dphilp_40MeV", filt_nue_ccqe, 0.04),
    new distributions::Mult("nue_ccqe_multp", filt_nue_ccqe, 2212),
    new distributions::Mult("nue_ccqe_multp_30MeV", filt_nue_ccqe, 2212, 0.03),
    new distributions::Mult("nue_ccqe_multn", filt_nue_ccqe, 2112),
    new distributions::Mult("nue_ccqe_multpip", filt_nue_ccqe, 211),
    new distributions::Mult("nue_ccqe_multpim", filt_nue_ccqe, -211),
    new distributions::Mult("nue_ccqe_multpi0", filt_nue_ccqe, 111),
    new distributions::Mult("nue_ccqe_multkp", filt_nue_ccqe, 321),
    new distributions::Mult("nue_ccqe_multkm", filt_nue_ccqe, -321),
    new distributions::Mult("nue_ccqe_multk0", filt_nue_ccqe, 311),

    // numCCMEC
    new distributions::Q0Q3("num_ccmec_q0q3", filt_num_ccmec),
    new distributions::Pke("num_ccmec_ppp", filt_num_ccmec),
    new distributions::PPLead("num_ccmec_pp", filt_num_ccmec),
    new distributions::ThetaPLead("num_ccmec_tp", filt_num_ccmec),
    new distributions::ThetaPLead("num_ccmec_tp_40MeV", filt_num_ccmec, 0.04),
    new distributions::ThetaLepPLead("num_ccmec_tlepp", filt_num_ccmec),
    new distributions::ThetaLepPLead("num_ccmec_tlepp_40MeV", filt_num_ccmec, 0.04),
    new distributions::dPhiLepPLead("num_ccmec_dphilp", filt_num_ccmec),
    new distributions::dPhiLepPLead("num_ccmec_dphilp_40MeV", filt_num_ccmec, 0.04),

    // numCCRes
    new distributions::Q0Q3("num_ccres_q0q3", filt_num_ccres),
    new distributions::W("num_ccres_w", filt_num_ccres),
    new distributions::PLep("num_ccres_plep", filt_num_ccres),
    new distributions::ThetaLep("num_ccres_tlep", filt_num_ccres),
    new distributions::PThetaLep("num_ccres_ptlep", filt_num_ccres),
    new distributions::PPiLead("num_ccres_ppi", filt_num_ccres),
    new distributions::ThetaPiLead("num_ccres_tpi", filt_num_ccres),
    new distributions::ThetaLepPiLead("num_ccres_tlpi", filt_num_ccres),
    new distributions::PPLead("num_ccres_pp", filt_num_ccres),
    new distributions::ThetaPLead("num_ccres_tp", filt_num_ccres),
    new distributions::ThetaPLead("num_ccres_tp_40MeV", filt_num_ccres, 0.04),
    new distributions::ThetaLepPLead("num_ccres_tlepp", filt_num_ccres),
    new distributions::ThetaLepPLead("num_ccres_tlepp_40MeV", filt_num_ccres, 0.04),
    new distributions::dPhiLepPLead("num_ccres_dphilp", filt_num_ccres),
    new distributions::dPhiLepPLead("num_ccres_dphilp_40MeV", filt_num_ccres, 0.04),
    new distributions::Mult("nue_ccres_multp", filt_num_ccres, 2212),
    new distributions::Mult("nue_ccres_multn", filt_num_ccres, 2112),
    new distributions::Mult("nue_ccres_multpip", filt_num_ccres, 211),
    new distributions::Mult("nue_ccres_multpim", filt_num_ccres, -211),
    new distributions::Mult("nue_ccres_multpi0", filt_num_ccres, 111),
    new distributions::Mult("nue_ccres_multkp", filt_num_ccres, 321),
    new distributions::Mult("nue_ccres_multkm", filt_num_ccres, -321),
    new distributions::Mult("nue_ccres_multk0", filt_num_ccres, 311)
  };

  size_t nevents = 0;

  // Event loop
  for (int ievent=0; ievent<nuistr.GetEntries(); ievent++) {
    if (ievent % 10000 == 0) {
      std::cout << "EVENT " << ievent << std::endl;
    }
    nuistr.GetEntry(ievent);

    for (Distribution* dist : dists) {
      if ((*dist->filter)(nuistr)) {
        dist->Fill(nuistr);
      }
    }
  } // end event loop

  // Save histograms (to file and PDF)
  TFile* fout = new TFile(outfile.c_str(), "recreate");
  for (Distribution* dist : dists) {
    if (dist->hist->GetEntries() > 0) {
      dist->Write();
      dist->Save();
    }
  }
  fout->Close();

  return 0;
}
