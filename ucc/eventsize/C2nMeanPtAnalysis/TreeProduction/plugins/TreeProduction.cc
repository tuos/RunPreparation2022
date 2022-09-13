// -*- C++ -*-
//
// Package:    C2nMeanPtAnalysis/TreeProduction
// Class:      TreeProduction
// 
/**\class TreeProduction TreeProduction.cc C2nMeanPtAnalysis/TreeProduction/plugins/TreeProduction.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shengquan Tuo
//         Created:  Mon, 09 Aug 2021 23:12:17 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include <TH1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TTree.h>
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/HeavyIonEvent/interface/CentralityBins.h"

using namespace std;
using namespace edm;
using namespace reco;

  int maxNchAnalysis = 300;

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class TreeProduction : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit TreeProduction(const edm::ParameterSet&);
      ~TreeProduction();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
   edm::Service<TFileService> fs;
edm::EDGetTokenT<TrackCollection> srcTracks_;
edm::EDGetTokenT<VertexCollection> srcVertex_;
edm::EDGetTokenT<CaloTowerCollection> srcTower_;
  edm::EDGetTokenT< reco::Centrality > centralityTag_;
  edm::EDGetTokenT< int > centralityBinTag_;
bool useQuality_;
reco::TrackBase::TrackQuality trackQuality_;
   TH1D* vxHist;
   TH1D* vyHist;
   TH1D* vzHist;
   TH1D* generalTracksHist;
   TH1D* ptHist;
   TH1D* etaHist;
   TH1D* phiHist;
   TH1D* hHF;
   TH1D* hHFplus;
   TH1D* hHFminus;
   TH2D* hetaVSphi;
   TH1D* hdzOerr;
   TH1D* hd0Oerr;
   TH1D* hpterrOpt;

      TTree* _tree_events;
      // vetex
      float _vz;
      float _vy;
      float _vx;

      int _centralityBin;

      // tracks
      static const int _nTrkMax = 1500;
      int _nTrk;
      float _trackPt[_nTrkMax];
      float _trackEta[_nTrkMax];
      float _trackPhi[_nTrkMax];

      float _trackPtErrOverPt[_nTrkMax];
      float _trackDzOverDzSigma[_nTrkMax];
      float _trackDxyOverDxySigma[_nTrkMax];

     
      int _cent;
      int _run;
      int _lumi;
      int _event;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TreeProduction::TreeProduction(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   usesResource("TFileService");
edm::Service<TFileService> fs;
srcTracks_ = consumes<TrackCollection>(iConfig.getParameter<edm::InputTag>("srcTracks"));
srcVertex_ = consumes<VertexCollection>(iConfig.getParameter<edm::InputTag>("srcVertex"));
srcTower_ = consumes<CaloTowerCollection>(iConfig.getParameter<edm::InputTag>("srcTower"));
useQuality_ = iConfig.getParameter<bool>("UseQuality");
trackQuality_ = TrackBase::qualityByName(iConfig.getParameter<std::string>("TrackQuality"));
centralityTag_ = consumes<reco::Centrality>(iConfig.getParameter<edm::InputTag>("centrality"));
centralityBinTag_ = consumes<int>(iConfig.getParameter<edm::InputTag>("centralityBin"));

TH1::SetDefaultSumw2();
vxHist = fs->make<TH1D>("vxhist","offlinePrimaryVertices Vx Distribution", 100, -0.5, 0.5);
vyHist = fs->make<TH1D>("vyhist","offlinePrimaryVertices Vy Distribution", 100, -0.5, 0.5);
vzHist = fs->make<TH1D>("vzhist","offlinePrimaryVertices Vz Distribution", 120, -30., 30.);
generalTracksHist = fs->make<TH1D>("generaltrackshist","generalTracks Distribution", 100, 0., 300.);
ptHist = fs->make<TH1D>("pthist","generalTracks pT Distribution", 100, 0., 10.);
etaHist = fs->make<TH1D>("etahist","generalTracks eta Distribution", 120, -3.0, 3.0);
phiHist = fs->make<TH1D>("phihist","generalTracks phi Distribution", 160, -4.0, 4.0);
hHF = fs->make<TH1D>("hfhist","HF Distribution", 200, 0., 200.);
hHFplus = fs->make<TH1D>("hfplushist","HF Plus Distribution", 200, 0., 200.);
hHFminus = fs->make<TH1D>("hfminushist","HF Minus Distribution", 200, 0., 200.);
hetaVSphi = fs->make<TH2D>("hetavsphi","generalTracks phi VS eta", 120, -3.0, 3.0, 160, -4.0, 4.0);
hdzOerr = fs->make<TH1D>("hdzoerr","dz/dzErr", 100, 0., 10.);
hd0Oerr = fs->make<TH1D>("hd0oerr","d0/d0Err", 100, 0., 10.);
hpterrOpt = fs->make<TH1D>("hpterropt","p_{T}Err/p_{T}", 100, 0., 0.5);

  _tree_events = fs->make<TTree>("trackTree", "track tree"); //make output tree

  // tracks
  _tree_events->Branch("cent", &_cent, "cent/I"); 
  _tree_events->Branch("run", &_run, "run/I"); 
  _tree_events->Branch("lumi", &_lumi, "lumi/I"); 
  _tree_events->Branch("event", &_event, "event/I"); 


}


TreeProduction::~TreeProduction()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
TreeProduction::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;


    //access centrality bins
    int cent = -1;

    edm::Handle<reco::Centrality> centrality;
    iEvent.getByToken(centralityTag_, centrality);
    edm::Handle<int> cbin;
    iEvent.getByToken(centralityBinTag_, cbin);
    //cent = *cbin;
    cent = (int) *cbin;
    //hist_cent_->Fill(cent);

//   auto cbin = iEvent.getHandle( centralityBinTag_ );
//   int cent = -1;
//   cent = ( int ) (*cbin);

//    cout<<"cent = "<<cent<<endl;
    if(cent==0 || cent==1){
      cout<<cent<<"  "<<iEvent.id().run()<<":"<<iEvent.id().luminosityBlock() <<":"<<iEvent.id().event()<<endl;
    }
    _cent = cent;
    _run = iEvent.id().run();
    _lumi = iEvent.id().luminosityBlock();
    _event = iEvent.id().event();

    //if(cent<60) return;
/*
    double etHFtowerSumPlus = 0;
    double etHFtowerSumMinus = 0;
    double etHFtowerSum = 0;
    Handle<CaloTowerCollection> towers;
    iEvent.getByToken(srcTower_,towers);
    for( size_t i = 0; i<towers->size(); ++ i){
       const CaloTower & tower = (*towers)[ i ];
       double eta = tower.eta();
       bool isHF = tower.ietaAbs() > 29;
          if(isHF && eta > 0){
            etHFtowerSumPlus += tower.pt();
          }
          if(isHF && eta < 0){
            etHFtowerSumMinus += tower.pt();
          }
    }
    etHFtowerSum = etHFtowerSumPlus + etHFtowerSumMinus;
    hHF->Fill(etHFtowerSum);
    hHFplus->Fill(etHFtowerSumPlus);
    hHFminus->Fill(etHFtowerSumMinus);

     double vx=-999.;
     double vy=-999.;
     double vz=-999.;
     double vxError=-999.;
     double vyError=-999.;
     double vzError=-999.;
     edm::Handle<VertexCollection> recoVertices;
     iEvent.getByToken(srcVertex_,recoVertices);
     unsigned int daughter = 0;
     int greatestvtx = 0;
     for (unsigned int i = 0 ; i< recoVertices->size(); ++i){
      daughter = (*recoVertices)[i].tracksSize();
      if( daughter > (*recoVertices)[greatestvtx].tracksSize()) greatestvtx = i;
     }
     if(recoVertices->size()>0){
      vx = (*recoVertices)[greatestvtx].position().x();
      vy = (*recoVertices)[greatestvtx].position().y();
      vz = (*recoVertices)[greatestvtx].position().z();
      vxError = (*recoVertices)[greatestvtx].xError();
      vyError = (*recoVertices)[greatestvtx].yError();
      vzError = (*recoVertices)[greatestvtx].zError();
     }
     vxHist->Fill(vx);
     vyHist->Fill(vy);
     vzHist->Fill(vz);
     
     if(fabs(vz)>15) return;

     _vz = vz;
     _vy = vy;
     _vx = vx;
     _centralityBin = cent;

     edm::Handle<TrackCollection> tracks;
     iEvent.getByToken(srcTracks_,tracks);
     int nTracks = 0;
     _nTrk = 0;
     for(unsigned int i = 0 ; i < tracks->size(); ++i){
       const Track& track = (*tracks)[i];
       if(!track.quality(trackQuality_)) continue;
       math::XYZPoint v1(vx,vy, vz);
       double dz= track.dz(v1);
       double dzsigma2 = track.dzError()*track.dzError()+vzError*vzError;
       double dxy= track.dxy(v1);
       double dxysigma2 = track.dxyError()*track.dxyError()+vxError*vyError;
       const double pterrcut = 0.1;
       const double dzrelcut = 5.0; //3.0
       const double dxyrelcut = 5.0; //3.0
       if( track.quality(trackQuality_) &&
       track.pt()>0.3 && track.pt()<100 && 
       track.eta()>-2.4 && track.eta()<2.4 &&
       track.ptError()/track.pt() < pterrcut &&
       dz*dz < dzrelcut*dzrelcut * dzsigma2 &&
       dxy*dxy < dxyrelcut*dxyrelcut * dxysigma2 ){
         ptHist->Fill(track.pt());
         etaHist->Fill(track.eta());
         phiHist->Fill(track.phi());
         nTracks++;
         hetaVSphi->Fill(track.eta(), track.phi());

       _trackPt[_nTrk] = track.pt();
       _trackEta[_nTrk] = track.eta();
       _trackPhi[_nTrk] = track.phi();

       _trackPtErrOverPt[_nTrk] = std::abs( track.ptError() ) / track.pt();
       _trackDzOverDzSigma[_nTrk] = track.dz(v1) / sqrt(fabs(track.dzError()*track.dzError()+vzError*vzError));
       _trackDxyOverDxySigma[_nTrk] = track.dxy(v1) / sqrt(fabs(track.dxyError()*track.dxyError()+vxError*vyError));

       _nTrk++;
       }
       hdzOerr->Fill(sqrt(fabs(dz*dz/dzsigma2)));
       hd0Oerr->Fill(sqrt(fabs(dxy*dxy/dxysigma2)));
       hpterrOpt->Fill(track.ptError()/track.pt());
     }
     generalTracksHist->Fill(nTracks);

  if(_nTrk==0 || _nTrk>maxNchAnalysis) return;
*/
  _tree_events->Fill();


#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
TreeProduction::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TreeProduction::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TreeProduction::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TreeProduction);
