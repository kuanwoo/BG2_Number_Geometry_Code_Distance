/*
  Copyright 2013  Vasiliy Usatyuk.
  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
  more details.

  You should have received a copy of the GNU General Public License along
  with this program; see the file COPYING.  If not, write to the Free
  Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
  02111-1307, USA.

*/

#include "targetver.h"
#include <time.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <sstream>
#include <iostream>
#include <assert.h>
#include <fstream>
#include <string>

#include "..\..\NTL\LLL.h"
#include "..\..\NTL\ZZ_px.h"
#include "..\..\NTL\ZZX.h"
NTL_CLIENT;
#include "..\..\tools.h"


using namespace std;


// Minkowski UpperBound of shortes vector in d-dimension Lattice based on Hermitian constant
// Shortest vector <= sqr (Hermitian const for d)* det(Lattice Basis)^(1/d)
// Hermitian constant approximately equal 0.2342*d+ O(1) 
//RR ShortVectorUpperBound(const mat_ZZ &A){

	
	int main(int argc, char **argv){	
	//int _tmain(int argc, _TCHAR* argv[]){
	system("cls");


	time_t timer1,timer2;
	mat_ZZ B;
	mat_ZZ B2;
	ZZ det2;  
	ZZ seed;
	seed=-1;  // was  seed=1
	long n = -1;  // was n = 82
	long bit = -1; // bit= 10
	short input=-1;
	long a = -1;
	long b = -1;
	long prune=0;
	long deep=0;
	long verbose = 0;
	short multiprecision = -1;
	short doublefloat = -1;
	short xdouble = -1;
	short quadfloat = -1;
	short extenexpondoubles = -1;
	short generate = -1;
	short ideal = -1;
	short index = -1;
	short lll = -1; 
	double delta = -1; 
	short bkz_block_size = -1;	
	 short tofile= -1;
// Parsing of command line
	PARSE_MAIN_ARGS {
//Take basis of Lattice from Goldshtein-Mayer generator 
	MATCH_MAIN_ARGID("--gen", generate);
//Take basis of Lattice from  ideal lattice generator 
	MATCH_MAIN_ARGID("--ideal", ideal);
//index of cyclotomic polynomials
	MATCH_MAIN_ARGID("--index", index);
//Define dimension of lattice (basis matrix) 
	MATCH_MAIN_ARGID("--dim",n);
//Define number of seed for random number genrator
	MATCH_MAIN_ARGID("--seed",seed);
//Define number of bit (decimal size of number) in coordinate represent
	MATCH_MAIN_ARGID("--bit",bit);
//Take basis of Lattice from  file with way to file
	MATCH_MAIN_ARGID("--inp", input);
//Reduce basis by LLL algorithm
	MATCH_MAIN_ARGID("--lll", lll); 
//Define delta = a/b;
	MATCH_MAIN_ARGID("--a", a);
	MATCH_MAIN_ARGID("--b", b);
// Use deep insertion in LLL
	MATCH_MAIN_ARGID("--deep", deep);
//Reduce basis by BKZ algorithm with block size equal
	MATCH_MAIN_ARGID("--bkz", bkz_block_size ); 
//Define delta of BKZ
	MATCH_MAIN_ARGID("--delta", delta);
//Choise precision of basis reductione algorithms 
	MATCH_MAIN_ARGID("--dp", doublefloat);
	MATCH_MAIN_ARGID("--qp", quadfloat);
	MATCH_MAIN_ARGID("--xd", extenexpondoubles);	
	MATCH_MAIN_ARGID("--mp", multiprecision);
//Print in file
	MATCH_MAIN_ARGID("--file", tofile);
//Using Schorr pruning technic
MATCH_MAIN_ARGID("--prune", prune);
	
	SYNTAX();
    }
	/*printf ("\nYour choice command line parameters: \n");
	if (generate!=-1) {
		printf ("\n Your choice generate Lattice \n");
		printf ("\n Size of lattice equal : %d \n",n );
		if (seed!=-1) printf ("\n Randomness of seed genetor equal : %d \n",seed );
		if (bit!=-1) printf ("\n Number of bit in coordinate represent equal : %d \n",bit );
	}
	if (strcmp(filename,"0")) printf ("\n Take basis of Lattice from file %s \n",filename );
	
	_getch();
*/

	if(generate==-1&&input==-1&&ideal==-1) {
	PrintOptionCML();
	
	} 

else{
	if(ideal==1&&seed!=-1&&index!=-1 ){
    

  
 
    
   
    ZZX phi=find_cyclotomic(index);  
    long n=deg(phi);
    ZZ det=find_determinant(index,10*n,seed);
    ZZ alpha=find_unity_root(index,det,phi);
    
   
    B.SetDims(n,n); 
    clear(B);
    B(1,1) = det;

    for (long i=2; i<=n; i++)
      {
	B(i,1)=det-PowerMod(alpha,i-1,det);
	B(i,i)=1;
      }
    
    
	PrintLattice(B);
	B2=B;
	ofstream myfile;
			time_t clock = time(NULL);
			struct tm *tmCurrent =localtime(&clock);
			char szTime[32];
			sprintf(szTime, "%d-%d-%d-%d-%d-%d-%s", tmCurrent->tm_mday, tmCurrent->tm_mon, tmCurrent->tm_year+1900,tmCurrent->tm_hour,tmCurrent->tm_min ,tmCurrent->tm_sec,"result.txt");
			myfile.open(szTime);
		    printf("\nResult save in %s\n",szTime);
			myfile << B<<endl;
		

			myfile << "Calculation demand : " << difftime(timer2, timer1) << " second\n";
			if(seed!=-1) myfile << "Seed is : " << seed <<endl;
			if(index!=-1) myfile << "Index is : " << index <<endl;
	
			PrintInFileMinVector(B2, myfile);
			myfile.close();
	}
	
	if(generate==1&&n!=-1&&seed!=-1&&bit!=-1 ) {
	B=Generate_randHNF_Lattice( n,  bit, seed);
	PrintLattice(B);
	}
	else
	if(generate==1&&n!=-1) {
	printf("\nSeed and bit set by default, seed=0, bit=10.\n\n");
    seed=0;
	bit=10;
	B=Generate_randHNF_Lattice( n,  bit, seed);
	PrintLattice(B);
	} 
	
	if(generate==1&&n==-1) printf(" Incorrect or not set dimmension of Lattice, --dim");
	
	if(input==1){
		printf("Please enter basis of Lattice by form [[ x1 x2 ... xn] ... [z1 z2 ... zn]] : \n");
		SetLattice(B);
		printf("\n Basis of lattice succesfull entered. \n Begining the reduction process... \n\n");
	}
	B2=B;

	

if(a!=-1&&b!=-1&&lll==1){
		
if (quadfloat==-1&&doublefloat==-1&&extenexpondoubles==-1&&multiprecision==-1){
			printf("\n\nPrecision type don't define. We shall use double by default.\n");
			time(&timer1);
			
			LLL_QP( B2, (double) a/b,deep );
			time(&timer2);
			
			
			PrintLattice(B2);
			PrintMinVector(B2);
			cout << "Calculation demand : " << difftime(timer2, timer1) << " second\n";
			
			if(tofile==1){
			ofstream myfile;
			time_t clock = time(NULL);
			struct tm *tmCurrent =localtime(&clock);
			char szTime[32];
			sprintf(szTime, "%d-%d-%d-%d-%d-%d-%s", tmCurrent->tm_mday, tmCurrent->tm_mon, tmCurrent->tm_year+1900,tmCurrent->tm_hour,tmCurrent->tm_min ,tmCurrent->tm_sec,"result.txt");
			myfile.open(szTime);
		    printf("\nResult save in %s\n",szTime);
			myfile << B<<endl;
			myfile << "Lattice reduced by LLL default set quazi quad precision, delta "<<(double) a/b << endl;
			if(deep!=0) myfile << "Lattice reduced by LLL with deep insertion:" <<deep<<endl;
			myfile << "Calculation demand : " << difftime(timer2, timer1) << " second\n";
			if(seed!=-1) myfile << "Seed is : " << seed <<endl;
			if(index!=-1) myfile << "Index is : " << index <<endl;
			myfile << B2<<endl;
			PrintInFileMinVector(B2, myfile);
			myfile.close();
								}

																				}	
	else {
			
			
		
		
			if(doublefloat==1){
			time(&timer1);
			long lResultRank = LLL( det2, B2, a, b, verbose );
			time(&timer2);
			PrintLattice(B2);
			PrintMinVector(B2);
			cout << "Calculation demand : " << difftime(timer2, timer1) << " second\n";
			
			if(tofile==1){
			ofstream myfile;
			time_t clock = time(NULL);
			struct tm *tmCurrent =localtime(&clock);
			char szTime[32];
			sprintf(szTime, "%d-%d-%d-%d-%d-%d-%s", tmCurrent->tm_mday, tmCurrent->tm_mon, tmCurrent->tm_year+1900,tmCurrent->tm_hour,tmCurrent->tm_min ,tmCurrent->tm_sec,"result.txt");
			myfile.open(szTime);
		    printf("\nResult save in %s\n",szTime);
			myfile << B<<endl;
			myfile << "Lattice reduced by LLL double  precision, delta "<<(double) a/b << endl;
			if(deep!=0) myfile << "Lattice reduced by LLL with deep insertion:" <<deep<<endl;
			myfile << "Calculation demand : " << difftime(timer2, timer1) << " second\n";
			if(seed!=-1) myfile << "Seed is : " << seed <<endl;
			if(index!=-1) myfile << "Index is : " << index <<endl;
			myfile << B2<<endl;
		    PrintInFileMinVector(B2, myfile);
			myfile.close();
			}
			}
			
			if(quadfloat==1) {
			time(&timer1);
			LLL_QP( B2, (double) a/b,deep );
			time(&timer2);
			PrintLattice(B2);
			PrintMinVector(B2);
			cout << "Calculation demand : " << difftime(timer2, timer1) << " second\n";
			if(tofile==1){
			ofstream myfile;
			time_t clock = time(NULL);
			struct tm *tmCurrent =localtime(&clock);
			char szTime[32];
			sprintf(szTime, "%d-%d-%d-%d-%d-%d-%s", tmCurrent->tm_mday, tmCurrent->tm_mon, tmCurrent->tm_year+1900,tmCurrent->tm_hour,tmCurrent->tm_min ,tmCurrent->tm_sec,"result.txt");
			myfile.open(szTime);
		    printf("\nResult save in %s\n",szTime);
			myfile << B<<endl;
			myfile << "Lattice reduced by LLL quazi quad precision, delta "<<(double) a/b << endl;
			if(deep!=0) myfile << "Lattice reduced by LLL with deep insertion:" <<deep<<endl;
			myfile << "Calculation demand : " << difftime(timer2, timer1) << " second\n";
			if(seed!=-1)  myfile << "Seed is : " << seed <<endl;
			if(index!=-1) myfile << "Index is : " << index <<endl;
			myfile << B2<<endl;
		    PrintInFileMinVector(B2, myfile);
			myfile.close();
			}
			}

			if(extenexpondoubles==1) {
			time(&timer1);
		    LLL_XD( B2, (double) a/b,deep );
			time(&timer2);
			PrintLattice(B2);
			PrintMinVector(B2);
			cout << "Calculation demand : " << difftime(timer2, timer1) << " second\n";
			if(tofile==1){
			ofstream myfile;
			time_t clock = time(NULL);
			struct tm *tmCurrent =localtime(&clock);
			char szTime[32];
			sprintf(szTime, "%d-%d-%d-%d-%d-%d-%s", tmCurrent->tm_mday, tmCurrent->tm_mon, tmCurrent->tm_year+1900,tmCurrent->tm_hour,tmCurrent->tm_min ,tmCurrent->tm_sec,"result.txt");
			myfile.open(szTime);
		    printf("\nResult save in %s\n",szTime);
			myfile << B<<endl;
			myfile << "Lattice reduced by LLL extended exponent doubles precision, delta "<<(double) a/b << endl;
			if(deep!=0) myfile << "Lattice reduced by LLL with deep insertion:" <<deep<<endl;
			myfile << "Calculation demand : " << difftime(timer2, timer1) << " second\n";
			if(seed!=-1)  myfile << "Seed is : " << seed <<endl;
			if(index!=-1) myfile << "Index is : " << index <<endl;
			myfile << B2<<endl;
			PrintInFileMinVector(B2, myfile);
			myfile.close();
			}
			}
			if(multiprecision==1) {
			time(&timer1);
			LLL_RR( B2, (double) a/b,deep);
			time(&timer2);
			PrintLattice(B2);
			PrintMinVector(B2);
			cout << "Calculation demand : " << difftime(timer2, timer1) << " second\n";
			if(tofile==1){
			ofstream myfile;
			time_t clock = time(NULL);
			struct tm *tmCurrent =localtime(&clock);
			char szTime[32];
			sprintf(szTime, "%d-%d-%d-%d-%d-%d-%s", tmCurrent->tm_mday, tmCurrent->tm_mon, tmCurrent->tm_year+1900,tmCurrent->tm_hour,tmCurrent->tm_min ,tmCurrent->tm_sec,"result.txt");
			myfile.open(szTime);
		    printf("\nResult save in %s\n",szTime);
			myfile << B<<endl;
			myfile << "Lattice reduced by LLL arbitry lenght precision, delta "<<(double) a/b << endl;
			if(deep!=0) myfile << "Lattice reduced by LLL with deep insertion:" <<deep<<endl;
			myfile << "Calculation demand : " << difftime(timer2, timer1) << " second\n";
			if(seed!=-1) myfile << "Seed is : " << seed <<endl;
			if(index!=-1) myfile << "Index is : " << index <<endl;
			myfile << B2<<endl;
			PrintInFileMinVector(B2, myfile);
			myfile.close();
			}
			}
			
		}




}



if(delta!=-1&&bkz_block_size!=-1){
			if (quadfloat==-1&&doublefloat==-1&&extenexpondoubles==-1&&multiprecision==-1){
			printf("\n\nPrecision type don't define. We shall use double by default.\n");
			time(&timer1);
			BKZ_QP( B2, delta,bkz_block_size,prune);
			time(&timer2);
			cout << "Lattice reduced by BKZ quazi quad precision, delta "<< delta << endl;
			PrintLattice(B2);
			PrintMinVector(B2);
			cout << "Calculation demand : " << difftime(timer2, timer1) << " second\n";
			if(tofile==1){
			ofstream myfile;
			time_t clock = time(NULL);
			struct tm *tmCurrent =localtime(&clock);
			char szTime[32];
			sprintf(szTime, "%d-%d-%d-%d-%d-%d-%s", tmCurrent->tm_mday, tmCurrent->tm_mon, tmCurrent->tm_year+1900,tmCurrent->tm_hour,tmCurrent->tm_min ,tmCurrent->tm_sec,"result.txt");
			myfile.open(szTime);
		    printf("\nResult save in %s\n",szTime);
			myfile << B<<endl;
			myfile << "Lattice reduced by BKZ quazi quad precision, delta "<< delta << endl;
			myfile << "Lattice reduced by BKZ block-size: "<<bkz_block_size<< endl;
			if(prune!=0) myfile << "We use pruning parameter p: "<<prune<< endl;
			myfile << "Calculation demand : " << difftime(timer2, timer1) << " second\n";
			if(seed!=-1) myfile << "Seed is : " << seed <<endl;
			if(index!=-1) myfile << "Index is : " << index <<endl;
			myfile << B2<<endl;
		    PrintInFileMinVector(B2, myfile);
			myfile.close();
			}

			}	

			if(doublefloat==1){
			time(&timer1);
			BKZ_FP( B2, delta,bkz_block_size,prune);
			time(&timer2);
			PrintLattice(B2);
			PrintMinVector(B2);
			cout << "Calculation demand : " << difftime(timer2, timer1) << " second\n";
			
			if(tofile==1){
			ofstream myfile;
			time_t clock = time(NULL);
			struct tm *tmCurrent =localtime(&clock);
			char szTime[32];
			sprintf(szTime, "%d-%d-%d-%d-%d-%d-%s", tmCurrent->tm_mday, tmCurrent->tm_mon, tmCurrent->tm_year+1900,tmCurrent->tm_hour,tmCurrent->tm_min ,tmCurrent->tm_sec,"result.txt");
			myfile.open(szTime);
		    printf("\nResult save in %s\n",szTime);
			myfile << B<<endl;
			myfile << "Lattice reduced by BKZ double  precision, delta "<<delta << endl;
			myfile << "Lattice reduced by BKZ block-size: "<<bkz_block_size<< endl;
			if(prune!=0) myfile << "We use pruning parameter p: "<<prune<< endl;
			myfile << "Calculation demand : " << difftime(timer2, timer1) << " second\n";
			if(seed!=-1) myfile << "Seed is : " << seed <<endl;
			if(index!=-1) myfile << "Index is : " << index <<endl;
			myfile << B2<<endl;
		    PrintInFileMinVector(B2, myfile);
			myfile.close();
			}
			}
			
			if(quadfloat==1) {
			time(&timer1);
			BKZ_QP( B2, delta,bkz_block_size,prune);
			time(&timer2);
			PrintLattice(B2);
			PrintMinVector(B2);
			cout << "Calculation demand : " << difftime(timer2, timer1) << " second\n";
			
			if(tofile==1){
			ofstream myfile;
			time_t clock = time(NULL);
			struct tm *tmCurrent =localtime(&clock);
			char szTime[32];
			sprintf(szTime, "%d-%d-%d-%d-%d-%d-%s", tmCurrent->tm_mday, tmCurrent->tm_mon, tmCurrent->tm_year+1900,tmCurrent->tm_hour,tmCurrent->tm_min ,tmCurrent->tm_sec,"result.txt");
			myfile.open(szTime);
		    printf("\nResult save in %s\n",szTime);
			myfile << B<<endl;
			myfile << "Lattice reduced by BKZ quazi quad precision, delta "<< delta << endl;
			myfile << "Lattice reduced by BKZ block-size: "<<bkz_block_size<< endl;
			if(prune!=0) myfile << "We use pruning parameter p: "<<prune<< endl;
			myfile << "Calculation demand : " << difftime(timer2, timer1) << " second\n";
			if(seed!=-1) myfile << "Seed is : " << seed <<endl;
			if(index!=-1) myfile << "Index is : " << index <<endl;
			myfile << B2<<endl;
		    PrintInFileMinVector(B2, myfile);
			myfile.close();
			}
			}

			if(extenexpondoubles==1) {
			time(&timer1);
		    BKZ_XD( B2, delta,bkz_block_size,prune);
			time(&timer2);
			PrintLattice(B2);
			PrintMinVector(B2);
			cout << "Calculation demand : " << difftime(timer2, timer1) << " second\n";
			if(tofile==1){
			ofstream myfile;
			time_t clock = time(NULL);
			struct tm *tmCurrent =localtime(&clock);
			char szTime[32];
			sprintf(szTime, "%d-%d-%d-%d-%d-%d-%s", tmCurrent->tm_mday, tmCurrent->tm_mon, tmCurrent->tm_year+1900,tmCurrent->tm_hour,tmCurrent->tm_min ,tmCurrent->tm_sec,"result.txt");
			myfile.open(szTime);
		    printf("\nResult save in %s\n",szTime);
			myfile << B<<endl;
			myfile << "Lattice reduced by BKZ extended exponent doubles precision, delta "<<delta<< endl;
			myfile << "Lattice reduced by BKZ block-size: "<<bkz_block_size<< endl;
			if(prune!=0) myfile << "We use pruning parameter p: "<<prune<< endl;
			myfile << "Calculation demand : " << difftime(timer2, timer1) << " second\n";
			if(seed!=-1) myfile << "Seed is : " << seed <<endl;
			if(index!=-1) myfile << "Index is : " << index <<endl;
			myfile << B2<<endl;
			PrintInFileMinVector(B2, myfile);
			myfile.close();
			}
			}
			if(multiprecision==1) {
			time(&timer1);
			BKZ_RR( B2, delta,bkz_block_size);
			time(&timer2);
			PrintLattice(B2);
			PrintMinVector(B2);
			cout << "Calculation demand : " << difftime(timer2, timer1) << " second\n";
			if(tofile==1){
			ofstream myfile;
			time_t clock = time(NULL);
			struct tm *tmCurrent =localtime(&clock);
			char szTime[32];
			sprintf(szTime, "%d-%d-%d-%d-%d-%d-%s", tmCurrent->tm_mday, tmCurrent->tm_mon, tmCurrent->tm_year+1900,tmCurrent->tm_hour,tmCurrent->tm_min ,tmCurrent->tm_sec,"result.txt");
			myfile.open(szTime);
		    printf("\nResult save in %s\n",szTime);
			myfile << B<<endl;
			myfile << "Lattice reduced by BKZ arbitry lenght precision, delta: "<<delta<< endl;
			myfile << "Lattice reduced by BKZ block-size: "<<bkz_block_size<< endl;
			if(prune!=0) myfile << "We use pruning parameter p: "<<prune<< endl;
			myfile << "Calculation demand : " << difftime(timer2, timer1) << " second\n";
			if(seed!=-1) myfile << "Seed is : " << seed <<endl;
			if(index!=-1) myfile << "Index is : " << index <<endl;
			myfile << B2<<endl;
			PrintInFileMinVector(B2, myfile);
			myfile.close();
			}
			}








}









}
	

		

	




/*
 B=Generate_randHNF_Lattice( n,  bit, seed);
  ofstream myfile;
  myfile.open ("F:\\example.txt");
  myfile << B;
  myfile.close();

  PrintLattice(B);
 _getch();
	SetLattice(B);
	cout<<endl;
	mat_ZZ B2 = B;
	mat_ZZ B3 = B;
	ZZ det2;  
	long a = 99; 
	long b = 100;
	long verbose = 0;

	long lResultRank = LLL( det2, B2, a, b, verbose );
	//PrintLattice(B2);
	PrintMinVector(B2);
    _getch();
	time(&timer1);
	G_BKZ_FP(B3); //solve 70 dimension 60 place in hall of fame (norm 2143)
	//G_BKZ_QP(B3,0.999,32); // solve 72 dimension 58 place in hall of fame (norm 2234)
	//G_BKZ_QP1(B3,0.999999,40); solve 82 dimension 46 place in hall of fame (norm 2303)
	//PrintLattice(B3);
	time(&timer2);

	cout << "Calculation demand : " << difftime(timer2, timer1) << " second\n";

	PrintMinVector(B3);
	//cout << "\n Closure of algorithm : " << LatticeVolumeClosure(B2,B3) << endl;
	
	_getch();
	
*/
	printf("Press any key to return in to the command line...\n");
	_getch();
	return 0;
}


