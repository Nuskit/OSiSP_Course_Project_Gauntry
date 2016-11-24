#include "stdafx.h"
#include "Direct_Operations.h"
#include "Global_Effect.h"

VOID ObjectFromX::Free_Start()
{
	MaterialBuffer = NULL;
	MaterialAmount = NULL;
	Mesh = NULL;
	Textures = NULL;
	Material_ALL = NULL;
}

ObjectFromX::ObjectFromX()
{
	Free_Start();
}

ObjectFromX::ObjectFromX(CONST WCHAR *NameFile,char* Folder, D3DXVECTOR3 Pos, DWORD Scale, HRESULT &ResultCreate)
{
	Free_Start();
	ID3DXBuffer* adjBuffer = NULL;

	Position = Pos;
	SCale = Scale;
	// Загрузка данных из X-файла
	//
	if (FAILED(D3DXLoadMeshFromX(
		NameFile, D3DXMESH_MANAGED, g_pd3dDevice, NULL,
		&MaterialBuffer, &adjBuffer, &MaterialAmount, &Mesh))
		)
		ResultCreate = E_FAIL;
	else
	{
		LoadTextureFromX(Folder);

		ResultCreate = S_OK;
	}
}

HRESULT ObjectFromX::LoadingObject(CONST WCHAR *NameFile, char* Folder, D3DXVECTOR3 Pos, DWORD Scale)
{
	ID3DXBuffer* adjBuffer = NULL;

	Position = Pos;
	SCale = Scale;
	MaterialBuffer = NULL;
	MaterialAmount = NULL;
	Mesh = NULL;
	Textures = NULL;
	Material_ALL = NULL;
	// Загрузка данных из X-файла
	//
	if (FAILED(D3DXLoadMeshFromX(
		NameFile, D3DXMESH_MANAGED, g_pd3dDevice, NULL,
		&MaterialBuffer, &adjBuffer, &MaterialAmount, &Mesh))
		)
		return  E_FAIL;
	else
	{
		LoadTextureFromX(Folder);

		return  S_OK;
	}
}

ObjectFromX::~ObjectFromX()
{
	if (Mesh != NULL)
		Mesh->Release();

	if (Textures != NULL)
		delete[]Textures;
	
	if (Material_ALL != NULL)
		delete[]Material_ALL;
}

D3DXVECTOR3 ObjectFromX::Get_Position()
{
	return Position;
}

VOID ObjectFromX::Set_Scaling(DWORD &New_Scaling)
{
	SCale = New_Scaling;
}
DWORD ObjectFromX::Get_Scaling()
{
	return SCale;
}

VOID ObjectFromX::Set_Position(D3DXVECTOR3 &New_position)
{
	Position = New_position;
}

VOID ObjectFromX::LoadTextureFromX(char *Folder)
{
	//
	// Извлечение материалов и загрузка текстур
	//
	if (MaterialBuffer != NULL && MaterialAmount != NULL)
	{
		Material_ALL = new D3DMATERIAL9[MaterialAmount];
		Textures = new LPDIRECT3DTEXTURE9[MaterialAmount];

		D3DXMATERIAL* MaterialFounding = (D3DXMATERIAL*)MaterialBuffer->
			GetBufferPointer();

		char PositionTexture[60] = { 0 };


		for (DWORD i = 0; i < MaterialAmount; ++i)
		{
			// При загрузке в свойстве MatD3D не устанавливается
			// значение для фонового света, поэтому установим его
			// сейчас
			MaterialFounding[i].MatD3D.Ambient = MaterialFounding[i].MatD3D.Diffuse;
			
			Textures[i] = NULL;
			// Сохраняем i-ый материал
			Material_ALL[i] = MaterialFounding[i].MatD3D;

			// Проверяем, связана ли с i-ым материалом текстура
			if (MaterialFounding[i].pTextureFilename != NULL)
			{
				// Да, загружаем текстуру для i-ой подгруппы
				strcpy(PositionTexture, Folder);
				strcat(PositionTexture, MaterialFounding[i].pTextureFilename);

				D3DXCreateTextureFromFileA(
					g_pd3dDevice,
					PositionTexture,
					&Textures[i]);
			}
		}

		if (MaterialBuffer != NULL)
		{
			MaterialBuffer->Release();
			MaterialBuffer = NULL;
		}
	}
}

VOID Camera::getViewMatrix()
{
	// Делаем оси камеры ортогональными
	D3DXVec3Normalize(&_look, &_look);
	D3DXVec3Cross(&_up, &_look, &_right);
	D3DXVec3Normalize(&_up, &_up);
	D3DXVec3Cross(&_right, &_up, &_look);
	D3DXVec3Normalize(&_right, &_right);

	// Строим матрицу вида:
	float x = -D3DXVec3Dot(&_right, &_pos);
	float y = -D3DXVec3Dot(&_up, &_pos);
	float z = -D3DXVec3Dot(&_look, &_pos);
	(*V)(0, 0) = _right.x;
	(*V)(0, 1) = _up.x;
	(*V)(0, 2) = _look.x;
	(*V)(0, 3) = 0.0f;
	(*V)(1, 0) = _right.y;
	(*V)(1, 1) = _up.y;
	(*V)(1, 2) = _look.y;
	(*V)(1, 3) = 0.0f;
	(*V)(2, 0) = _right.z;
	(*V)(2, 1) = _up.z;
	(*V)(2, 2) = _look.z;
	(*V)(2, 3) = 0.0f;
	(*V)(3, 0) = x;
	(*V)(3, 1) = y;
	(*V)(3, 2) = z;
	(*V)(3, 3) = 1.0f;
}

//удалить впоследствии
VOID Camera::setViewMatrix()
{
	_right.x = (*V)(0, 0);
	_up.x = (*V)(0, 1);
	_look.x = (*V)(0, 2);
	_right.y = (*V)(1, 0);
	_up.y = (*V)(1, 1);
	_look.y = (*V)(1, 2);
	_right.z = (*V)(2, 0);
	_up.z = (*V)(2, 1);
	_look.z = (*V)(2, 2);
	_pos.x = (*V)(3, 0);
	_pos.y = (*V)(3, 1);
	_pos.z = (*V)(3, 2);

	// Строим матрицу вида:
	float x = -D3DXVec3Dot(&_right, &_pos);
	float y = -D3DXVec3Dot(&_up, &_pos);
	float z = -D3DXVec3Dot(&_look, &_pos);

	// Делаем оси камеры ортогональными
	D3DXVec3Normalize(&_look, &_look);
	D3DXVec3Cross(&_up, &_look, &_right);
	D3DXVec3Normalize(&_up, &_up);
	D3DXVec3Cross(&_right, &_up, &_look);
	D3DXVec3Normalize(&_right, &_right);
}

void Camera::setCameraType(CameraType cameraType)
{
	_cameraType = cameraType;
}

void Camera::getPosition(D3DXVECTOR3* pos)
{
	*pos = _pos;
}

void Camera::setPosition(D3DXVECTOR3* pos)
{
	_pos = *pos;
}

void Camera::getRight(D3DXVECTOR3* right)
{
	*right = _right;
}

void Camera::getUp(D3DXVECTOR3* up)
{
	*up = _up;
}

void Camera::getLook(D3DXVECTOR3* look)
{
	*look = _look;
}

VOID Camera::pitch(float angle)
{
	D3DXMATRIX T;
	D3DXMatrixRotationAxis(&T, &_right, angle);
	// Поворот векторов _up и _look относительно вектора _right
	D3DXVec3TransformCoord(&_up, &_up, &T);
	D3DXVec3TransformCoord(&_look, &_look, &T);
}
VOID Camera::yaw(float angle)
{
	D3DXMATRIX T;
	// Для наземных объектов выполняем вращение
	// вокруг мировой оси Y (0, 1, 0)
	if (_cameraType == LANDOBJECT)
		D3DXMatrixRotationY(&T, -angle);
	// Для летающих объектов выполняем вращение
	// относительно верхнего вектора
	if (_cameraType == AIRCRAFT)
		D3DXMatrixRotationAxis(&T, &_up, angle);
	// Поворот векторов _right и _look относительно
	// вектора _up или оси Y
	D3DXVec3TransformCoord(&_right, &_right, &T);
	D3DXVec3TransformCoord(&_look, &_look, &T);
}
VOID Camera::roll(float angle)
{
	// Вращение только для летающих объектов
	if (_cameraType == AIRCRAFT)
	{
		D3DXMATRIX T;
		D3DXMatrixRotationAxis(&T, &_look, angle);
		// Поворот векторов _up и _right относительно
		// вектора _look
		D3DXVec3TransformCoord(&_right, &_right, &T);
		D3DXVec3TransformCoord(&_up, &_up, &T);
	}
}
void Camera::walk(float units)
{
	// Для наземных объектов перемещение только в плоскости xz
	if (_cameraType == LANDOBJECT)
		_pos += D3DXVECTOR3(_look.x, 0.0f, _look.z) * units;
	if (_cameraType == AIRCRAFT)
		_pos += _look * units;
}
void Camera::strafe(float units)
{
	// Для наземных объектов перемещение только в плоскости xz
	if (_cameraType == LANDOBJECT)
		_pos += D3DXVECTOR3(_right.x, 0.0f, _right.z) * units;
	if (_cameraType == AIRCRAFT)
		_pos += _right * units;
}
void Camera::fly(float units)
{
	if (_cameraType == AIRCRAFT)
		_pos += _up * units;
}

Camera::Camera()
{
	V = new D3DXMATRIX(
		-1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		-8000.0f, -500.0f, -8000.0f, 1.0f
	);



	_cameraType = AIRCRAFT;

	setViewMatrix();
}

Camera::Camera(CameraType cameraType)
{
	V = new D3DXMATRIX(
		1.0f, 0.0f, 0.00f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.00f, 0.0f, 1.0f, 0.0f,
		0.0f, -20.0f, 0.0f, 1.0f
		);

	_cameraType = cameraType;

	setViewMatrix();
}

Camera::~Camera()
{
	delete V;
}


const DWORD Terrain::TerrainVertex::FVF = D3DFVF_XYZ |D3DFVF_TEX1;

Terrain::Terrain(IDirect3DDevice9* device,
	char* heightmapFileName,
	int numVertsPerRow,
	int numVertsPerCol,
	int cellSpacing,
	float heightScale)
{
	_device = device;
	_numVertsPerRow = numVertsPerRow;
	_numVertsPerCol = numVertsPerCol;
	_cellSpacing = cellSpacing;

	_numCellsPerRow = _numVertsPerRow - 1;
	_numCellsPerCol = _numVertsPerCol - 1;

	_width = _numCellsPerRow * _cellSpacing;
	_depth = _numCellsPerCol * _cellSpacing;

	_numVertices = _numVertsPerRow * _numVertsPerCol;
	_numTriangles = _numCellsPerRow * _numCellsPerCol * 2;

	_heightScale = heightScale;

	// load heightmap
	if (!readRawFile(heightmapFileName))
	{
		::MessageBox(0, L"readRawFile - FAILED", 0, 0);
		::PostQuitMessage(0);
		
	}
	else
	{

		// scale heights
		for (int i = 0; i < _heightSize; i++)
			_heightmap[i] *= heightScale;

		// compute the vertices
		if (!computeVertices())
		{
			::MessageBox(0, L"computeVertices - FAILED", 0, 0);
			::PostQuitMessage(0);
		}

		// compute the indices
		if (!computeIndices())
		{
			::MessageBox(0, L"computeIndices - FAILED", 0, 0);
			::PostQuitMessage(0);
		}
	}
}

Terrain::~Terrain()
{
	if (_vb != NULL)
		_vb->Release();
	if (_ib != NULL)
		_ib->Release();
	if (_tex != NULL)
		_tex->Release();

	delete[] _heightmap;
}

int Terrain::getHeightmapEntry(int row, int col)
{
	return _heightmap[row * _numVertsPerRow + col];
}

void Terrain::setHeightmapEntry(int row, int col, int value)
{
	_heightmap[row * _numVertsPerRow + col] = value;
}

bool Terrain::computeVertices()
{
	HRESULT hr = 0;

	hr = _device->CreateVertexBuffer(
		_numVertices * sizeof(TerrainVertex),
		D3DUSAGE_WRITEONLY,
		TerrainVertex::FVF,
		D3DPOOL_MANAGED,
		&_vb,
		0);

	if (FAILED(hr))
		return false;

	// coordinates to start generating vertices at
	int startX = -_width / 2;
	int startZ = _depth / 2;

	// coordinates to end generating vertices at
	int endX = _width / 2;
	int endZ = -_depth / 2;

	// compute the increment size of the texture coordinates
	// from one vertex to the next.
	float uCoordIncrementSize = 1.0f / (float)_numCellsPerRow;
	float vCoordIncrementSize = 1.0f / (float)_numCellsPerCol;

	TerrainVertex* v = 0;
	_vb->Lock(0, 0, (void**)&v, 0);

	int i = 0;
	for (int z = startZ; z >= endZ; z -= _cellSpacing)
	{
		int j = 0;
		for (int x = startX; x <= endX; x += _cellSpacing)
		{
			// compute the correct index into the vertex buffer and heightmap
			// based on where we are in the nested loop.
			int index = i * _numVertsPerRow + j;

			v[index] = TerrainVertex(
				(float)x,
				(float)_heightmap[index],
				(float)z,
				(float)j * uCoordIncrementSize,
				(float)i * vCoordIncrementSize);

			j++; // next column
		}
		i++; // next row
	}

	_vb->Unlock();

	return true;
}

bool Terrain::computeIndices()
{
	HRESULT hr = 0;

	hr = _device->CreateIndexBuffer(
		_numTriangles * 3 * sizeof(WORD), // 3 indices per triangle
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&_ib,
		0);

	if (FAILED(hr))
		return false;

	WORD* indices = 0;
	_ib->Lock(0, 0, (void**)&indices, 0);

	// index to start of a group of 6 indices that describe the
	// two triangles that make up a quad
	int baseIndex = 0;

	// loop through and compute the triangles of each quad
	for (int i = 0; i < _numCellsPerCol; i++)
	{
		for (int j = 0; j < _numCellsPerRow; j++)
		{
			indices[baseIndex] = i   * _numVertsPerRow + j;
			indices[baseIndex + 1] = i   * _numVertsPerRow + j + 1;
			indices[baseIndex + 2] = (i + 1) * _numVertsPerRow + j;

			indices[baseIndex + 3] = (i + 1) * _numVertsPerRow + j;
			indices[baseIndex + 4] = i   * _numVertsPerRow + j + 1;
			indices[baseIndex + 5] = (i + 1) * _numVertsPerRow + j + 1;

			// next quad
			baseIndex += 6;
		}
	}

	_ib->Unlock();

	return true;
}

bool Terrain::loadTexture(WCHAR* fileName)
{
	HRESULT hr = 0;

	hr = D3DXCreateTextureFromFile(
		_device,
		fileName,
		&_tex);

	if (FAILED(hr))
		return false;

	return true;
}

bool Terrain::genTexture(D3DXVECTOR3* directionToLight)
{
	// Method fills the top surface of a texture procedurally.  Then
	// lights the top surface.  Finally, it fills the other mipmap
	// surfaces based on the top surface data using D3DXFilterTexture.

	HRESULT hr = 0;

	// texel for each quad cell
	int texWidth = _numCellsPerRow;
	int texHeight = _numCellsPerCol;

	if (_tex != NULL)
		_tex->Release();
	// create an empty texture
	hr = D3DXCreateTexture(
		_device,
		texWidth, texHeight,
		0, // create a complete mipmap chain
		0, // usage
		D3DFMT_X8R8G8B8,// 32 bit XRGB format
		D3DPOOL_MANAGED, &_tex);

	if (FAILED(hr))
		return false;

	D3DSURFACE_DESC textureDesc;
	_tex->GetLevelDesc(0 /*level*/, &textureDesc);

	// make sure we got the requested format because our code 
	// that fills the texture is hard coded to a 32 bit pixel depth.
	if (textureDesc.Format != D3DFMT_X8R8G8B8)
		return false;

	D3DLOCKED_RECT lockedRect;
	_tex->LockRect(0/*lock top surface*/, &lockedRect,
		0 /* lock entire tex*/, 0/*flags*/);

	DWORD* imageData = (DWORD*)lockedRect.pBits;
	for (int i = 0; i < texHeight; i++)
	{
		for (int j = 0; j < texWidth; j++)
		{
			D3DXCOLOR c;

			// get height of upper left vertex of quad.
			float height = (float)getHeightmapEntry(i, j) / _heightScale;

			if ((height) < 42.5f) 		 c = d3d::BEACH_SAND;
			else if ((height) < 85.0f)	 c = d3d::LIGHT_YELLOW_GREEN;
			else if ((height) < 127.5f) c = d3d::PUREGREEN;
			else if ((height) < 170.0f) c = d3d::DARK_YELLOW_GREEN;
			else if ((height) < 212.5f) c = d3d::DARKBROWN;
			else	                     c = d3d::WHITE;

			// fill locked data, note we divide the pitch by four because the
			// pitch is given in bytes and there are 4 bytes per DWORD.
			imageData[i * lockedRect.Pitch / 4 + j] = (D3DCOLOR)c;
		}
	}

	_tex->UnlockRect(0);

	if (!lightTerrain(directionToLight))
	{
		::MessageBox(0, L"lightTerrain() - FAILED", 0, 0);
		return false;
	}

	hr = D3DXFilterTexture(
		_tex,
		0, // default palette
		0, // use top level as source level
		D3DX_DEFAULT); // default filter

	if (FAILED(hr))
	{
		::MessageBox(0, L"D3DXFilterTexture() - FAILED", 0, 0);
		return false;
	}

	return true;
}

bool Terrain::lightTerrain(D3DXVECTOR3* directionToLight)
{
	HRESULT hr = 0;

	D3DSURFACE_DESC textureDesc;
	_tex->GetLevelDesc(0 /*level*/, &textureDesc);

	// make sure we got the requested format because our code that fills the
	// texture is hard coded to a 32 bit pixel depth.
	if (textureDesc.Format != D3DFMT_X8R8G8B8)
		return false;

	D3DLOCKED_RECT lockedRect;
	_tex->LockRect(
		0,          // lock top surface level in mipmap chain
		&lockedRect,// pointer to receive locked data
		0,          // lock entire texture image
		0);         // no lock flags specified

	DWORD* imageData = (DWORD*)lockedRect.pBits;
	for (int i = 0; i < textureDesc.Height; i++)
	{
		for (int j = 0; j < textureDesc.Width; j++)
		{
			// index into texture, note we use the pitch and divide by 
			// four since the pitch is given in bytes and there are 
			// 4 bytes per DWORD.
			int index = i * lockedRect.Pitch / 4 + j;

			// get current color of quad
			D3DXCOLOR c(imageData[index]);

			// shade current quad
			c *= computeShade(i, j, directionToLight);;

			// save shaded color
			imageData[index] = (D3DCOLOR)c;
		}
	}

	_tex->UnlockRect(0);

	return true;
}

float Terrain::computeShade(int cellRow, int cellCol, D3DXVECTOR3* directionToLight)
{
	// get heights of three vertices on the quad
	float heightA = getHeightmapEntry(cellRow, cellCol);
	float heightB = getHeightmapEntry(cellRow, cellCol + 1);
	float heightC = getHeightmapEntry(cellRow + 1, cellCol);

	// build two vectors on the quad
	D3DXVECTOR3 u(_cellSpacing, heightB - heightA, 0.0f);
	D3DXVECTOR3 v(0.0f, heightC - heightA, -_cellSpacing);

	// find the normal by taking the cross product of two
	// vectors on the quad.
	D3DXVECTOR3 n;
	D3DXVec3Cross(&n, &u, &v);
	D3DXVec3Normalize(&n, &n);

	float cosine = D3DXVec3Dot(&n, directionToLight);

	if (cosine < 0.0f)
		cosine = 0.0f;

	return cosine;
}


HRESULT Terrain::readRawFile(char* fileName)
{
	_heightmap = NULL;


	ifstream inFile(fileName, ios_base::binary);
	if (!inFile.is_open())
		return false;

	inFile.seekg(0, ios::end);
	_heightSize = inFile.tellg();
	inFile.seekg(0, ios::beg);

	// Высота для каждой вершины
	BYTE *in = new BYTE[_heightSize];
	inFile.read(
		(char*)in, // буффер
		_heightSize); // количество читаемых в буфер байт
	inFile.close();
	// копируем вектор BYTE в вектор int
	_heightmap = new DWORD[_heightSize];
	for (int i = 0; i < _heightSize; i++)
		_heightmap[i] = in[i];

	delete[]in;
	return true;
}

float Terrain::getHeight(float x, float z)
{
	// Translate on xz-plane by the transformation that takes
	// the terrain START point to the origin.
	x = ((float)_width / 2.0f) + x;
	z = ((float)_depth / 2.0f) - z;

	// Scale down by the transformation that makes the 
	// cellspacing equal to one.  This is given by 
	// 1 / cellspacing since; cellspacing * 1 / cellspacing = 1.
	x /= (float)_cellSpacing;
	z /= (float)_cellSpacing;

	// From now on, we will interpret our positive z-axis as
	// going in the 'down' direction, rather than the 'up' direction.
	// This allows to extract the row and column simply by 'flooring'
	// x and z:

	float col = ::floorf(x);
	float row = ::floorf(z);

	// get the heights of the quad we're in:
	// 
	//  A   B
	//  *---*
	//  | / |
	//  *---*  
	//  C   D

	float A = getHeightmapEntry(row, col);
	float B = getHeightmapEntry(row, col + 1);
	float C = getHeightmapEntry(row + 1, col);
	float D = getHeightmapEntry(row + 1, col + 1);

	//
	// Find the triangle we are in:
	//

	// Translate by the transformation that takes the upper-left
	// corner of the cell we are in to the origin.  Recall that our 
	// cellspacing was nomalized to 1.  Thus we have a unit square
	// at the origin of our +x -> 'right' and +z -> 'down' system.
	float dx = x - col;
	float dz = z - row;

	// Note the below compuations of u and v are unneccessary, we really
	// only need the height, but we compute the entire vector to emphasis
	// the books discussion.
	float height = 0.0f;
	if (dz < 1.0f - dx)  // upper triangle ABC
	{
		float uy = B - A; // A->B
		float vy = C - A; // A->C

		// Linearly interpolate on each vector.  The height is the vertex
		// height the vectors u and v originate from {A}, plus the heights
		// found by interpolating on each vector u and v.
		height = A + d3d::Lerp(0.0f, uy, dx) + d3d::Lerp(0.0f, vy, dz);
	}
	else // lower triangle DCB
	{
		float uy = C - D; // D->C
		float vy = B - D; // D->B

		// Linearly interpolate on each vector.  The height is the vertex
		// height the vectors u and v originate from {D}, plus the heights
		// found by interpolating on each vector u and v.
		height = D + d3d::Lerp(0.0f, uy, 1.0f - dx) + d3d::Lerp(0.0f, vy, 1.0f - dz);
	}

	return height;
}

bool Terrain::draw(D3DXMATRIX* world, bool drawTris)
{
	HRESULT hr = 0;

	if (_device)
	{
		_device->SetTransform(D3DTS_WORLD, world);

		_device->SetStreamSource(0, _vb, 0, sizeof(TerrainVertex));
		_device->SetFVF(TerrainVertex::FVF);
		_device->SetIndices(_ib);

		_device->SetTexture(0, _tex);

		// turn off lighting since we're lighting it ourselves
		_device->SetRenderState(D3DRS_LIGHTING, false);

		hr = _device->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			0,
			0,
			_numVertices,
			0,
			_numTriangles);

		_device->SetRenderState(D3DRS_LIGHTING, true);

		if (drawTris)
		{
			_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			hr = _device->DrawIndexedPrimitive(
				D3DPT_TRIANGLELIST,
				0,
				0,
				_numVertices,
				0,
				_numTriangles);

			_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}

		if (FAILED(hr))
			return false;
	}

	return true;
}


VOID physics ::Check_Camera(Camera &Current_Camera,Terrain *Current_Terrain)
{
	static FLOAT Current_Height_Terrain;
	static D3DXVECTOR3 position;
	Current_Camera.getPosition(&position);
	Current_Height_Terrain = Check_Terrain(Current_Terrain, position.x, position.z);

	if (Current_Height_Terrain - 254.0 < position.y)
	{
		if (fabs(Current_Height_Terrain - 254.0 - position.y)>10)
			position.y = Current_Height_Terrain - 254.0;
		Current_Camera.setCameraType(Camera::LANDOBJECT);
	}
	else
	{
		position.y += 7.0;
		Current_Camera.setCameraType(Camera::AIRCRAFT);
	}

	if (position.x > 9500)
		position.x -= 24;
	else 	if (position.x < -9500)
	position.x += 24;
	if (position.z > 9500)
		position.z -= 24;
	else 	if (position.z < -9500)
		position.z += 24;
	if (position.y > 9500)
		position.y -= 24;
	else 	if (position.y < -9500)
		position.y += 24;

	Current_Camera.setPosition(&position);
}


FLOAT physics ::Check_Terrain(Terrain *Current_Terrains,FLOAT x,FLOAT z)
{

	return Current_Terrains->getHeight(x,z);
}

VOID physics ::Position_From_Terrain(ObjectFromX &Objects,Terrain *Current_Terrain)
{
	static FLOAT Current_Height_Terrain;
	static D3DXVECTOR3 position;
	position = Objects.Get_Position();
	Current_Height_Terrain=Check_Terrain(Current_Terrain,position.x,position.z);
	
	if (Current_Height_Terrain - 24.0 < position.y)
	{
		if (fabs(Current_Height_Terrain - 24.0 - position.y)>5)
			position.y = Current_Height_Terrain - 24.0;
	}
	else
	{
			position.y += 7.0;
	}

	if (position.x > 9500)
		position.x -= 24;
	if (position.z > 9500)
		position.z -= 24;

	if (position.x < -9500)
		position.x += 24;
	if (position.z < -9500)
		position.z += 24;

	Objects.Set_Position(position);
}