#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>
#include <fstream>
using namespace std;

// http://en.wikipedia.org/wiki/ANSI_escape_code
const string redtty("\033[1;31m");   // tell tty to switch to red
const string greentty("\033[1;32m");   // tell tty to switch to bright green
const string bluetty("\033[1;34m");   // tell tty to switch to bright blue
const string magentatty("\033[1;35m");   // tell tty to switch to bright magenta
const string yellowbgtty("\033[1;43m");   // tell tty to switch to bright yellow background
const string underlinetty("\033[4m");   // tell tty to switch to underline
const string deftty("\033[0m");      // tell tty to switch back to default color

// Exec a string then print its time, e.g. TIME(init());
#define TIME(arg) { arg;  } ; ptime(#arg); 

time_t tStart;

void ptime(const char *const msg) {
  float t= ((float)clock())/CLOCKS_PER_SEC;
  float tr = difftime(time(NULL),tStart);
  cerr << magentatty << "Cumulative CPU time thru " << msg << "= " << t << "   |  Real time= " << tr << deftty << endl;
}

// Create a new array of size var of type.  Report error.
#define NEWA(var,type,size) { try  { if(0==(var=new type [(size)])) throw;} catch (...)  { cerr << "NEWA failed on " #var "=new " #type "[" #size "=" << (size) << "]" << endl; exit(1); }}


typedef  pair<int,int> pii;

class Point {
public:
  unsigned short int x,y;
 // short int z;
  
  Point(const short int y1, const short int x1) : 
    x(x1),y(y1) {}
};

/*bool operator<(const Point &a, const Point &b) {
  return a.z > b.z;
}*/




//Uses Young-He's algorithm to flood a terrain...
//Ref: http://www.google.com.br/url?sa=t&source=web&cd=3&ved=0CDIQFjAC&url=http%3A%2F%2Fwww.sciencedirect.com%2Fscience%2Farticle%2Fpii%2FS0098300405001937&ei=6FD2Tc-8JYSGhQfKxtjgBg&usg=AFQjCNF4EmCGPPtO6jCH1AMXyCzZbQcrNQ&sig2=oG8MIndi0fXNdixh_nXXvw

//Allocates matrix: dirs[nrows][nrows]

queue<Point> seaLevelQueues[65536];
void flood(short int **elevs,unsigned char **&dirs,const int nrows) {
	dirs = new unsigned char*[nrows]; 
  	for(int i=0;i<nrows;i++) {
		NEWA(dirs[i],unsigned char,nrows);
		for(int j=0;j<nrows;j++)
			dirs[i][j] = 0;
  	}

	//priority_queue<Point> seaLevelPQ;

	for (int i=0;i<nrows;i++) {		
		//seaLevelPQ.push( Point(i,0,elevs[i][0]) );
		//seaLevelPQ.push( Point(i,nrows-1,elevs[i][nrows-1]) );
		seaLevelQueues[elevs[i][0] + 32768].push(Point(i,0));
		seaLevelQueues[elevs[i][nrows-1]+ 32768].push(Point(i,nrows-1));

		dirs[i][0] = 128;
		dirs[i][nrows-1] = 8;
	}
	for (int i=1;i<nrows-1;i++) {
		//seaLevelPQ.push( Point(0,i,elevs[0][i]) );
		//seaLevelPQ.push( Point(nrows-1,i,elevs[nrows-1][i]) );
		seaLevelQueues[elevs[0][i]+ 32768].push(Point(0,i));
		seaLevelQueues[elevs[nrows-1][i]+ 32768].push(Point(nrows-1,i));

		dirs[0][i] =  2;
		dirs[nrows-1][i] = 32;
	}	

	
	int seaLevel = -32768;
	for(;seaLevel<=32767;seaLevel++) {
		while (!seaLevelQueues[seaLevel+32768].empty()) {	
			Point p = seaLevelQueues[seaLevel+32768].front(); seaLevelQueues[seaLevel+32768].pop();
		
			//seaLevel = p.z;

			if (p.y > 0 ) {
				if (p.x >0) {
					if (dirs[p.y-1][p.x-1]==0) {		
						dirs[p.y-1][p.x-1] = 16;		

						if ( elevs[ p.y-1][p.x-1 ] <= seaLevel )
							 elevs[ p.y-1][p.x-1 ] = seaLevel;
						seaLevelQueues[ 32768 +elevs[ p.y-1][p.x-1 ]].push( Point(p.y-1,p.x-1 ) );	
					}
				}

				if (dirs[p.y-1][p.x]==0)  {	
					dirs[p.y-1][p.x] = 32;		
	
					if ( elevs[ p.y-1][p.x ] <= seaLevel )
						 elevs[ p.y-1][p.x] = seaLevel;
					seaLevelQueues[ 32768 +elevs[ p.y-1][p.x ]].push( Point(p.y-1,p.x ) );	
				}

				if (p.x < nrows-1) {
					if (dirs[p.y-1][p.x+1]==0) {
						dirs[p.y-1][p.x+1] = 64;

						if ( elevs[ p.y-1][p.x+1 ] <= seaLevel )
							 elevs[ p.y-1][p.x+1 ] = seaLevel;
						seaLevelQueues[ 32768 +elevs[ p.y-1][p.x+1 ]].push( Point(p.y-1,p.x+1) );
					}	
				}
			} 
			if (p.x >0) {
				if (dirs[p.y][p.x-1]==0) {
					dirs[p.y][p.x-1] = 8;

					if ( elevs[ p.y][p.x-1 ] <= seaLevel )
						elevs[ p.y][p.x-1 ] = seaLevel;
					seaLevelQueues[ 32768 +elevs[p.y][p.x-1 ]  ].push( Point(p.y,p.x-1 ) );	
				}
			}
			if (p.x < nrows-1) {
				if (dirs[p.y][p.x+1]==0) { 
					dirs[p.y][p.x+1] = 128;

					if ( elevs[ p.y][p.x+1 ] <= seaLevel )
						elevs[ p.y][p.x+1 ] = seaLevel;
					seaLevelQueues[ 32768 +elevs[ p.y][p.x+1 ] ].push( Point(p.y,p.x+1 ) );	
				}
			}
	
			if (p.y < nrows-1 ) {
				if (p.x >0) {
					if (dirs[p.y+1][p.x-1]==0)  {
						dirs[p.y+1][p.x-1] = 4;

						if ( elevs[ p.y+1][p.x-1 ] <= seaLevel )
							 elevs[ p.y+1][p.x-1 ] = seaLevel;
						seaLevelQueues[ 32768 +elevs[ p.y+1][p.x-1 ] ].push( Point(p.y+1,p.x-1 ) );	
					}
				}

				if (dirs[p.y+1][p.x]==0)  {
					dirs[p.y+1][p.x] = 2;

					if ( elevs[ p.y+1][p.x ] <= seaLevel )
						 elevs[ p.y+1][p.x] = seaLevel;
					seaLevelQueues[ 32768 +elevs[ p.y+1][p.x ] ].push( Point(p.y+1,p.x ) );	
				}

				if (p.x < nrows-1) {
					if (dirs[p.y+1][p.x+1]==0) {
						dirs[p.y+1][p.x+1] = 1;

						if ( elevs[ p.y+1][p.x+1 ] <= seaLevel )
							 elevs[ p.y+1][p.x+1 ] = seaLevel;
						seaLevelQueues[ 32768 + elevs[ p.y+1][p.x+1 ] ].push( Point(p.y+1,p.x+1 ) );	
					}
				}
			} 
		}

	}
}



//Allocates matrix: elevs[nrows][nrows]
void readElevs(short int **&elevs,const int nrows) {
  elevs = new short int*[nrows];
  for(int i=0;i<nrows;i++) {
	NEWA(elevs[i],short int,nrows);
  }
  for (int i=0;i<nrows;i++) {
    cin.read(reinterpret_cast<char*>(elevs[i]), 2*nrows);    
  }
}

//Allocates matrix: elevs[nrows][nrows] 
void init(const int argc, const char **argv,short int **&elevs,int &nrows) {
	if (argc!=2) {
		cerr << "Error, use: rwflood nrows <input" << endl;
		exit(1);
	}

	tStart = time(NULL);
	nrows = atoi(argv[1]);
	readElevs(elevs,nrows);
}


void writeFlowDirs(unsigned char **dirs,const int nrows) {   
	for (int i=0; i<nrows; i++) {
		for (int j=0; j<nrows; j++) {			
			unsigned char tmp = dirs[i][j];
			cout.write(reinterpret_cast<char *>(&tmp),1);
		}
	}
}




int main(const int argc, const char **argv) {
	int nrows; //Number of rows in the terrain
	short int **elevs; //Elevation matrix, (we use signed shorts to represent elevation)

	
	TIME(init(argc,argv,elevs,nrows));


	unsigned char **dirs; //Flow direction matrix
		             // The direction of a cell c may be 1,2,4,8,16,32,64 or 128
		             // 1 means c points to the upper left cell, 2 -> upper cell, 
		             // 4 -> upper right , ...
		             // 1     2   4
		             // 128   c   8
		             // 64   32   16

  
	
	//Flood depressions and Compute directions
	TIME(flood(elevs,dirs,nrows));

	for(int i=0;i< nrows;i++) delete []elevs[i];
	delete []elevs;	

	//Write results...
	TIME(writeFlowDirs(dirs,nrows));

	for(int i=0;i< nrows;i++) delete []dirs[i];
	delete []dirs;
	
}
