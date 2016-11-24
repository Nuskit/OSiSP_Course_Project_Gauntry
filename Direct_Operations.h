#pragma once
#include "Global_Effect.h"
#include <fstream>
using namespace std;

class ObjectFromX;
class Terrain;
class Camera;

class physics 
{
public:
	static FLOAT Check_Terrain(Terrain *,FLOAT,FLOAT);
	static VOID Check_Camera(Camera &,Terrain*);
	static VOID Position_From_Terrain(ObjectFromX &,Terrain*);
};

class ObjectFromX
{
private:
	LPD3DXBUFFER MaterialBuffer;
	D3DXVECTOR3 Position;
	DWORD SCale;

	VOID LoadTextureFromX(char *);

	friend VOID physics ::Position_From_Terrain(ObjectFromX &,Terrain*);
	VOID Free_Start();
public:
	LPD3DXMESH Mesh;
	DWORD MaterialAmount;
	LPDIRECT3DTEXTURE9* Textures;
	D3DMATERIAL9* Material_ALL;

	ObjectFromX();
	ObjectFromX(CONST WCHAR *,char*, D3DXVECTOR3 ,DWORD ,HRESULT &);

	HRESULT LoadingObject(CONST WCHAR *, char*, D3DXVECTOR3, DWORD);
	~ObjectFromX();
	D3DXVECTOR3 Get_Position();
	VOID Set_Position(D3DXVECTOR3 &);
	DWORD Get_Scaling();
	VOID Set_Scaling(DWORD &);

};



class Camera
{
private:
	friend VOID physics ::Check_Camera(Camera &,Terrain*);
public:
	enum CameraType { LANDOBJECT, AIRCRAFT };
	LPD3DXMATRIX V;

	Camera();
	Camera(CameraType cameraType);
	~Camera();
	VOID strafe(float units); // влево/вправо
	VOID fly(float units); // вверх/вниз
	VOID walk(float units); // вперед/назад
	VOID pitch(float angle); // вращение относительно
	// правого вектора
	VOID yaw(float angle); // вращение относительно
	// верхнего вектора
	VOID roll(float angle); // вращение относительно
	// вектора взгляда
	VOID getViewMatrix();
	VOID setViewMatrix();
	VOID setCameraType(CameraType cameraType);
	VOID getPosition(D3DXVECTOR3* pos);
	VOID setPosition(D3DXVECTOR3* pos);
	VOID getRight(D3DXVECTOR3* right);
	VOID getUp(D3DXVECTOR3* up);
	VOID getLook(D3DXVECTOR3* look);
private:
	CameraType _cameraType;
	D3DXVECTOR3 _right;
	D3DXVECTOR3 _up;
	D3DXVECTOR3 _look;
	D3DXVECTOR3 _pos;
};

class Terrain
{
private:
	friend FLOAT physics ::Check_Terrain(Terrain *,FLOAT,FLOAT);

public:
	Terrain(
		IDirect3DDevice9* device,
		char* heightmapFileName,
		int numVertsPerRow,
		int numVertsPerCol,
		int cellSpacing,    // space between cells
		float heightScale);

	~Terrain();

	int  getHeightmapEntry(int row, int col);
	void setHeightmapEntry(int row, int col, int value);

	float getHeight(float x, float z);

	bool  loadTexture(WCHAR* fileName);
	bool  genTexture(D3DXVECTOR3* directionToLight);
	bool  draw(D3DXMATRIX* world, bool drawTris);

private:
	IDirect3DDevice9*       _device;
	IDirect3DTexture9*      _tex;
	IDirect3DVertexBuffer9* _vb;
	IDirect3DIndexBuffer9*  _ib;

	int _numVertsPerRow;
	int _numVertsPerCol;
	int _cellSpacing;

	int _numCellsPerRow;
	int _numCellsPerCol;
	int _width;
	int _depth;
	int _numVertices;
	int _numTriangles;

	float _heightScale;

	DWORD *_heightmap;
	DWORD _heightSize;

	// helper methods
	HRESULT  readRawFile(char *fileName);
	bool  computeVertices();
	bool  computeIndices();
	bool  lightTerrain(D3DXVECTOR3* directionToLight);
	float computeShade(int cellRow, int cellCol, D3DXVECTOR3* directionToLight);

	struct TerrainVertex
	{
		TerrainVertex(){}
		TerrainVertex(float x, float y, float z, float u, float v)
		{
			_x = x; _y = y; _z = z; _u = u; _v = v;
		}
		float _x, _y, _z;
		float _u, _v;

		static const DWORD FVF;
	};
};

