#include "loader.h"
#include "vertex.h"
#include "face.h"

#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/scene.h> // Output data structure
#include <assimp/postprocess.h> // Post processing flags
#include <iostream>
#include <unistd.h>

using namespace std;

const aiScene * currentScene;

string folder;

void constructVertex(aiVector3D & in, Vertex & out) {
	out = Vertex(in[0], in[1], in[2], 1);
}

void copyMaterials(SceneObject & obj) {
	//for (int i = 0; i < currentScene->mNumTextures; i++) {
	//	(currentScene->mTextures[i])
	//}
//	cout <<	currentScene->mNumTextures << endl;
	
	for (int i = 0; i < currentScene->mNumMaterials; i++) {
		aiMaterial * curMat = currentScene->mMaterials[i]; 

		aiString name;
		aiColor3D diffuse;
		aiColor3D specular;
		aiColor3D ambient;
		float Ns;
		float Tr;

		curMat->Get(AI_MATKEY_NAME, name);
		curMat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
		curMat->Get(AI_MATKEY_COLOR_SPECULAR, specular);
		curMat->Get(AI_MATKEY_COLOR_AMBIENT, ambient);		
		curMat->Get(AI_MATKEY_SHININESS, Ns);
		curMat->Get(AI_MATKEY_OPACITY, Tr);

		vector<double> * ambient_color = new vector<double>();
		vector<double> * diffuse_color = new vector<double>();
		vector<double> * specular_color = new vector<double>();

		ambient_color->push_back(ambient.r);
		ambient_color->push_back(ambient.g);
		ambient_color->push_back(ambient.b);

		diffuse_color->push_back(diffuse.r);
		diffuse_color->push_back(diffuse.g);
		diffuse_color->push_back(diffuse.b);
		
		specular_color->push_back(specular.r);
		specular_color->push_back(specular.g);
		specular_color->push_back(specular.b);

		aiString texName;
		curMat->GetTexture(aiTextureType_DIFFUSE, 0, &texName, NULL, NULL, NULL, NULL, NULL);

//        vector<string> blah = head->getTextures();

        //for (int i = 0; i < blah.size(); i++)  {

            //    cout << "Adding texture: " << texPath << endl;
          //      textures.push_back(TextureLoader::loadTexture(texPath));

        //}


	//	if (texPath.length > 0) {
		//	cout << "." << texPath.C_Str() << "." << endl;
	//		obj.addTexture(texPath.C_Str());
	//	}
	//	cout << curMat->GetTextureCount(aiTextureType_DIFFUSE) << endl;
//		cout << curMat->Get(AI_MATKEY_TEXTURE, 0).C_Str() << endl;


//		cout << diffuse.r << " " << diffuse.g << " " << diffuse.b << endl;
//		cout << ambient.r << " " << ambient.g << " " << ambient.b << endl;
//		cout << specular.r << " " << specular.g << " " << specular.b << endl;
//		cout << ambient << endl;
//		cout << specular << endl;
	
		Material * m = new Material(name.C_Str());
		obj.addMaterial(m);
		if (texName.length > 0) {
	  		char * cwd = new char[255];
        		getcwd(cwd, 255);
               		string texPath = "";
             		texPath.append(cwd);
                	texPath.append("/");
                	texPath.append(texName.C_Str());
			m->addTexture(texPath);
		}

		m->setAmbient(ambient_color);
		m->setDiffuse(diffuse_color);
		m->setSpecular(specular_color);
		m->setShininess(Ns);
		m->setTransparency(Tr);
	}	
}

void copyVertices(aiMesh * m, SceneObject & obj) {
	cout << "This mesh has " << m->GetNumUVChannels() << " channels. " << endl;
	for (int i = 0; i < m->mNumVertices; i++) {
		cout << "start vertex" << endl;
		Vertex v = Vertex(0,0,0,0);
		constructVertex(m->mVertices[i], v);
		
		if (!m->HasTextureCoords(0)) {
			cout << "\tAdd reg vertex" << endl;
			obj.addVertex(v);
		}
		else {
			cout << "\tAdd tex" << endl;
			Vertex * texV = new Vertex(0,0,0,0);
			constructVertex((m->mTextureCoords[0][i]), *texV);
			obj.addVertex(v, texV);
		}
	}
	
	/*for (int i = 0; i < m->mNumVertices; i++) {
		Vertex * v = new Vertex(0,0,0,0);
		constructVertex(m->mTextureCoords[i], v);
		obj.addTexVertex(v);
	}*/
}

void copyFaces(aiMesh * m, SceneObject & obj, int pivot) {
	
	for (int i = 0; i < m->mNumFaces; i++) {
		cout << "start face:" << endl;
		aiFace curFace = m->mFaces[i];
		Face * f = new Face(obj.getMaterial(m->mMaterialIndex));
		//cout << "face" << endl;
		for (int j = 0; j < curFace.mNumIndices; j++) {
			int index = curFace.mIndices[j];
			//cout << obj.getVertex(index);
			if (obj.hasTexCoord(index)) {
				cout << "\tAdd tex vertex" << endl;
				f->add_vertex(obj.getVertex(index), obj.getTexVertex(index));
			}
			else {
				cout << "\tAdd vertex" << endl;
				f->add_vertex(obj.getVertex(index));//, index);
			}
		}
		obj.addFace(f);
	}
}

void copyMeshes(aiNode & node, SceneObject & obj) {
	//cout << "Copy Meshes NYI." << endl;
	int pivot = 0;
	for (int i = 0; i < node.mNumMeshes; i++) {
		aiMesh * cur = currentScene->mMeshes[node.mMeshes[i]];
		copyVertices(cur, obj);
		copyFaces(cur, obj, pivot);
		pivot += cur->mNumVertices;
	}	
}
 
void traverseScene(aiNode& node, SceneObject & output, aiMatrix4x4& accTransform) {
//	SceneObject parent;

	if (node.mNumMeshes > 0) {
		output = SceneObject();
		copyMaterials(output);
		copyMeshes(node, output);
		// TODO: Deal with the node transform!!
	}
	else {
		//TODO: Deal with the node transform!!	
	}
	
	for (int i = 0; i < node.mNumChildren; i++) {
		//SceneObject * child = new SceneObject();
		//output.addChild(child);
		traverseScene(*node.mChildren[i], output, accTransform );
	}
	
/*	if (scene->HasCameras()) {
		cout << "Cameras: " << endl;;
		for (int i = 0; i < scene->mNumCameras; i++) {
			cout << (scene->mCameras)[i]->mName.C_Str() << endl;
		}
	}	
	if (scene->HasLights()) {
		cout << "Lights: " << endl;
		for (int i = 0; i < scene->mNumLights; i++) {
			cout << (scene->mLights)[i]->mName.C_Str() << endl;
		}
	}
        if (scene->HasMeshes()) {
                cout << "Meshes: " << endl;
                for (int i = 0; i < scene->mNumMeshes; i++) {
					if (scene->HasMaterials()) {
						//Todo extract material properties
						aiString name;
						(scene->mMaterials)[(scene->mMeshes)[i]->mMaterialIndex]->Get(AI_MATKEY_NAME, name);
						cout << name.C_Str() << endl;
					}
                    //    cout << "   ." <<  (scene->mMeshes)[i]->mName.C_Str() << "." << endl;
				//	}
			cout << "      Faces: " << endl;
			if ((scene->mMeshes)[i]->HasFaces()) {
				for (int j = 0; j < (scene->mMeshes)[i]->mNumFaces; j++) {
					cout << "         " << (scene->mMeshes)[i]->mFaces[j].mNumIndices << endl;	
				}
			}
                }
        }*/
}

void AssetLoader::loadAsset ( string filename, SceneObject & out) {
	// Create an instance of the Importer class
	Assimp::Importer importer;
	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll
	// propably to request more postprocessing than we do in this example.
	currentScene = importer.ReadFile( filename,
	aiProcess_CalcTangentSpace |
	aiProcess_Triangulate |
	aiProcess_JoinIdenticalVertices |
	aiProcess_SortByPType);
	// If the import failed, report it
	if( !currentScene) {
		//DoTheErrorLogging( importer.GetErrorString());
		cerr << "Failed to load '" << filename << "'" << endl;
		exit(1);
		//return false;
	}
	// Now we can access the file's contents.
	//SceneObject s;
	char * outstring = new char[PATH_MAX];
	realpath(filename.c_str(), outstring);
//	cout << "." << outstring << "." << endl;	
	
	folder = string(outstring);
	cout << folder << endl;
	traverseScene(*(currentScene->mRootNode), out,  currentScene->mRootNode->mTransformation);
	// We're done. Everything will be cleaned up by the importer destructor
	//return true;
}


/*int main (int argc, char * argv [] ) {
	if (argc < 2) {
		cerr << "Usage: " << argv[0] << " <MODEL> " << endl;
		exit(1);
	}
	cout << argv[1] << endl;
	DoTheImportThing(string(argv[1]));	
}*/
