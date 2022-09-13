void getEventList(){

Int_t cent, run, lumi, event;

TFile *infile = new TFile("./flow_data_PbPbMBAOD_tree_ESnohffilter.root","read");
        TTree *t1 = (TTree*)infile->Get("demo/trackTree");
        t1->SetBranchAddress("cent", &cent);
        t1->SetBranchAddress("run", &run);
        t1->SetBranchAddress("lumi", &lumi);
        t1->SetBranchAddress("event", &event);

int nEvt = t1->GetEntries();
ofstream outcent0;
outcent0.open("events_cent0.txt");
ofstream outcent1;
outcent1.open("events_cent1.txt");
ofstream outcentAll;
outcentAll.open("events_centAll.txt");

        for(int ne=0; ne<nEvt; ne++){
	    t1->GetEntry(ne);
            if(ne%100==0)  cout<<"Run "<<ne<<" of the total "<<nEvt<<" events; "<<endl;
            
            if(cent==0) outcent0<<run<<":"<<lumi<<":"<<event<<",";
            if(cent==1) outcent1<<run<<":"<<lumi<<":"<<event<<",";
            if(cent<200) outcentAll<<run<<":"<<lumi<<":"<<event<<",";

        }

outcent0.close();
outcent1.close();
outcentAll.close();

}


