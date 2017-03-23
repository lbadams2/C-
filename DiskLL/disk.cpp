#include "disk.h"
#include <fstream>

Sector *disk[NUMOFSECTORS];
list<SectorListNode> pool;// = new list<SectorListNode>();
list<DiskFile> files;// = new list<DiskFile>();

/*
 * disk array holds sectors, list of sector nodes indicates free sectors
 */

bool removeNode(const SectorListNode& node){
	return node.begin == -1;
}

int populateSectors(istream& file, char* fileName){
	string line;
	int i, tmpBegin, tmpEnd = 0;
	char *s;
	// get diskFile with same name as file
	list<DiskFile>::iterator i1 = files.begin();
	for(; i1 != files.end(); i1++) {
		while(*(i1->name) == *fileName && (*(i1->name) != '\0' || *fileName != '\0')){
			i1++;
			fileName++;
		}
		if(*(i1->name) == '\0' && *fileName == '\0')
			break;
	}
	while(getline(file, line)){
		i = 0;
		// get 3 characters to store in the disk array
		while(i < line.length()){
			if(i % 3 != 0)
				s = &line[i];
			else {
				++s = '\0'; // set the end of the string
				// what if there are no nodes in pool
				pool.remove_if(removeNode);
				SectorListNode &node = pool.front();
				disk[node.begin]->contents = s;
				i1 = files.begin();
				for(; i1 != files.end(); i1++){
					list<SectorListNode>::iterator sFI = i1->sectors->begin();
					// adjust list of sectors diskFile maintains to include this new location where its contents are stored if this location is
					// adjacent to an existing node in list maintained by diskFile
					for(; sFI != i1->sectors->end(); sFI++){
						tmpBegin = node.begin;
						tmpEnd = node.end;
						if(tmpBegin - 1 == sFI->end){
							sFI->end += 1;
							node.begin += 1;
							break;
						}
						else if(tmpEnd + 1 == sFI->begin){
							sFI->begin -= 1;
							node.end -= 1;
							break;
						}
					}
					// if there are no sectorListNodes in diskFile with a boundary adjacent to the sectorListNode popped from pool, create a new node to add to
					// the diskFile and modify the node popped from pool.
					if(sFI == i1->sectors->end()){
						SectorListNode newNode(node.begin, node.begin);
						i1->sectors->push_front(newNode);
						node.begin += 1;
					}
				}
					/*
					 * create the new node only if there is not a node in the linked list maintained in DiskFile that can be augmented to include
					 * this location.
					 */
				if(node.begin == node.end)
					node.begin = node.end = -1;// mark for removal
				else
					/*
					 * incrementing begin in this node prevents file from pointing to the node that has its data is stored.  this index must be put
					 * in another node
					 */
					node.begin += 1;
			}
			s++;
			i++;
		}
	}
	return 1;
}

void initializeDisk(){
	for(int i = 0; i < NUMOFSECTORS; i++)
		disk[i] = new Sector();
}


/*
 * need to make linked list of files and use the next fields in the linked list of sectorListNodes. file has a pointer to a list of sectors
 * containing the file. what is this pointing to? a linked list consists of different nodes pointing to one another, what is the list object? it
 * has methods for operating on the list
 */
int main(){
	ifstream file1("file1.txt");
	ifstream file2("file2.txt");
	ifstream file3("file3.txt");
	ifstream file4("file4.txt");
	DiskFile* diskFile4 = new DiskFile("file4.txt", file4.gcount(), nullptr);
	DiskFile* diskFile3 = new DiskFile("file3.txt", file3.gcount(), diskFile4);
	DiskFile* diskFile2 = new DiskFile("file2.txt", file2.gcount(), diskFile3);
	DiskFile* diskFile1 = new DiskFile("file1.txt", file1.gcount(), diskFile2);
	files.push_front(diskFile1);
	files.push_front(diskFile2);
	files.push_front(diskFile3);
	files.push_front(diskFile4);
	//files.push_front(file1);
	// create SectorListNodes
	pool.push_front(SectorListNode(0, 29));
	initializeDisk();
	if(!populateSectors(file1, "file1.txt"))
		cout << "Incomplete copy of file1";
	if(!populateSectors(file2, "file2.txt"))
		cout << "Incomplete copy of file2";
	if(!populateSectors(file3, "file3.txt"))
		cout << "Incomplete copy of file3";
	if(!populateSectors(file4, "file4.txt"))
		cout << "Incomplete copy of file4";
}
