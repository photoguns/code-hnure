#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

#define MAX_PATH 260

void reqestFileOpen(char *,fstream &);

int main (int argc,char *argv) {
	int offset=0, width=0, height=0, c=0, i=0;
	char buf[8], lett, buff, mode[3];
	while(1) {
		cout<<"Code/Decode/Exit?(C/D/E)";
		cin.getline(mode,3);
		cin.clear();
		_flushall();
		mode[1]='\0';
		if(toupper(mode[0])=='C') {

			fstream file,filem,fileo;

			reqestFileOpen("Input container filename(*.bmp): ",file);

			reqestFileOpen("Input message filename(*.txt): ",filem);

			reqestFileOpen("Input output filename(*.bmp): ",fileo);

			BITMAPFILEHEADER sbfh;
			BITMAPINFOHEADER sbih;

			file.read((char*)&sbfh,sizeof(BITMAPFILEHEADER));
			if(sbfh.bfType!='MB'){
				cout<<"This is not a BMP!!!";
				return 1;
			}
			file.read((char*)&sbih,sizeof(BITMAPINFOHEADER));

			offset=sbfh.bfOffBits;
			width=sbih.biWidth;
			height=(sbih.biHeight>0) ? sbih.biHeight : -sbih.biHeight;

			cout<<"\nU have "<<height*width*3<<"bit to hide UR info("<<((height*width*3)/8)<<"bytes/charters)\n\n";

			filem.seekg(0,ios::end);
			cout<<"UR msg is "<<filem.tellg()<<"bytes\n\n";
			filem.seekg(0,ios::beg);

			file.seekg(0);
			for(i=0;i<offset;i++)
				fileo.put(file.get());

			file.seekg(offset);
			char msg,bf;
			while(!filem.eof()) {
				filem.get(msg);
				for(i=0;i<8;i++) {
					file.read(&bf,1);
					if(msg%2)
						bf |= 1;
					else bf &= 0xFE;
					fileo.put(bf);
					msg/=2;
				}
			}

			while(!file.eof()){
				file.get(buf[0]);
				fileo.put(buf[0]);
			}

			fileo.close(); file.close(); filem.close();
			cout<<"\nDone!";
		}

		else if(toupper(mode[0])=='D') {

			fstream fileo,filet;

			reqestFileOpen("Input container filename(*.bmp): ",fileo);

			reqestFileOpen("Input output filename(*.txt): ",filet);

			fileo.seekg(10);
			fileo.read(buf,4);
			offset=(buf[3]<<3*8)+(buf[2]<<2*8)+(buf[1]<<8)+buf[0];

			fileo.seekg(18);
			fileo.read(buf,8);
			width=(buf[3]<<3*8)+(buf[2]<<2*8)+(buf[1]<<8)+buf[0];
			height=(buf[7]<<3*8)+(buf[6]<<2*8)+(buf[5]<<8)+buf[4];

			cout<<"\nThis file may containe "<<height*width*3<<"bit of hidden info("<<((height*width*3)/8)<<"bytes/charters)\n\n";

			fileo.seekg(offset);
			c=0;
			lett=0,buff=0;
			while(!fileo.eof()) {
				fileo.get(buff);
				lett+=((abs(buff%2))*(1<<c));
				if(c!=7)
					c++; 
				else {
					c=0;filet<<lett;lett=0;
				}
			}
			fileo.close();
			cout<<"\n\nDone!\n\n";
		}

		else if(toupper(mode[0])=='E') {

			system("Pause");
			return 0;

		}

		else cout<<"Error\n";

	}

	return 0;
}

void reqestFileOpen(char *outputChar,fstream &fobj) {
			cout<<outputChar;
			char fname[MAX_PATH];
			do {
				cin.getline(fname,MAX_PATH);
				cin.clear();
				_flushall();
				fobj.open(fname,ios::binary | ios::in | ios::out);
				if(!fobj) 
					cout<<"Wrong filename...Try again: ";
			}
			while(!fobj);
}