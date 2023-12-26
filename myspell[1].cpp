#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <map>
#include <vector>

#include "hashtable.h"

using namespace std;
using namespace cop4530;

struct top10{
   string word;
   int rank;
};
int main(int argc, char * argv[]){
   char * dict=argv[1];   //store command line param
   char * cfile=argv[2];
   char * outfile=argv[3];
   string line, wrd, rwrd;
   int rank, ich, rsize=10, ranknum=5000;
   string choice;
   bool eloop=true;
   HashTable<string> dtable;
   map<string, int> wrdRank;
   vector<top10> rWrds;   
   vector<top10>::iterator it;   
   top10 obj10;
   ofstream os;

   os.open(outfile, ios::trunc);   //clear file
   if(! os)
     cout<<"could not open output"<<endl;
   else{	  
      os.close();
    }

   ifstream in;
   in.open("wordrank.txt");
   if(! in)
      cout<<"wordrank is not open"<<endl;
   else{
      while(in.eof()==false)   //populate rank hash
      {
         in>>rwrd;
	 in>>rank;
	 in.ignore();
	 wrdRank[rwrd]=rank;
      }
   in.close();
   }//else

   if(dtable.load(dict)==false)   //store dictionary in table
      cout<<"did not store dictionary"<<endl;

   ifstream is;
   is.open(cfile);
   if(! is)
      cout<<"could not open check file"<<endl;
   else
   {
      int wrdind;
      string capwrd, stored, storedl, chwrd;
      while(is.eof()==false)
      {
         getline(is, line);   //read in line
         storedl=line;
         stringstream s(line);

         while(s>>stored){
	    wrd.clear();
            string lv=stored;
	    for(int i=0; i<stored.size();i++){   //remove punc
	        if(ispunct(stored[i])==false){
      		   wrd+=tolower(lv[i]);
   	    	}
	    }  //forloop

     	    if(dtable.contains(wrd)==true)
               ;
	    else{	    
	       wrdind=storedl.find(stored);   //find ind of wrd in str
//cap word vs lowercase
	       chwrd=wrd;
               for(int i=0; i<wrd.size();i++){   //change word to cap
		   capwrd+=toupper(wrd[i]);
	       }
		for(int i=0;i<wrd.size();i++){   //itr thru each letter
		   for(int j=97;j<123;j++){
			chwrd[i]=j;	
			if(dtable.contains(chwrd)==true){   //changed word in dictionary
			   if(wrdRank.find(chwrd)!=wrdRank.end()){  //word is ranked
				ranknum=wrdRank[chwrd];
			   }
			   obj10.word=chwrd;  //insert struct
			   obj10.rank=ranknum;
			   ranknum=5000;  //reset
			   if(rWrds.empty()==true){   //if empty
				rWrds.insert(rWrds.begin(),obj10);
			   }
			   else{
				it=rWrds.begin();
				int i=0;
				while(i<10){
				   if(obj10.rank<rWrds[i].rank){   //insert struct based off rank
					it+=i;
					rWrds.insert(it, obj10);
					i=10;
				   }
				   else if(i==rWrds.size()-1){
					rWrds.push_back(obj10);
					i=10;
				   }

				   i++;
				}//while
			   }   
			   
			}//if contain
		   }
		   chwrd=wrd;
		}
         //	}//else invalid wrd
                do{
		eloop=true;
//cout<<wrdind<<"\t"<<wrd.size()<<"\t"<<capwrd<<endl;
		cout<<endl<<line.replace(wrdind, wrd.size(), capwrd)<<endl;   //output line w/ wrd cap

		cout<<"========================================="<<endl;
//cout<<"vec size is"<<rWrds.size()<<endl;
		if(rWrds.size()<10)
		   rsize=rWrds.size();
		else
		   rsize=10;
		for(int i=0; i<rsize;i++)
		{
		   cout<<(i)<<"): "<<rWrds[i].word<<endl;
		}
		cout<<"n (no change):"<<endl;
		cout<<"========================================="<<endl;

		cout<<"Your choice: ";
		cin>>choice;
//cout<<choice<<endl;
 		if(isdigit(choice[0])){   //resume here
   		ich= stoi(choice);
   		if(ich<0 || ich>(rsize-1)){
      		   eloop=false;
      		   cout<<"Invalid choice"<<endl;
   		}
		}
   		else if(choice.front()!='n'){
      		   eloop=false;
      		   cout<<"Invalid choice"<<endl;
   		}
//}
                 }
		 while(eloop==false);
		
		if(choice=="n")
		   line.replace(wrdind, wrd.size(), wrd );
		else
  		   line.replace(wrdind, wrd.size(), rWrds[ich].word );

//		os.open(outfile);
	       capwrd.clear();
	       rWrds.clear();
	    }//else inval wrd
//            s>>wrd;   //gets word

	 }//while wrd
         os.open(outfile, ios::app);
	 if(! os)
	    cout<<"could not open output"<<endl;
	 else{
//	    cout<<line<<endl<<endl;
	    os<<line<<endl;
	    os.close();
	 }
      }//while eof
   is.close();
   }   //esle open

   return 0;
}

void menu()
{
	cout << "\n\n";
	cout << "l - Load Dictionary From File" << endl;
	cout << "a - Add Word" << endl;
	cout << "r - Remove Word" << endl;
	cout << "c - Clear HashTable" << endl;
	cout << "f - Find Word" << endl;
	cout << "d - Dump HashTable" << endl;
	cout << "s - HashTable Size" << endl;
	cout << "w - Write to File" << endl;
	cout << "x - Exit program" << endl;
	cout << "\nEnter choice : ";
}
