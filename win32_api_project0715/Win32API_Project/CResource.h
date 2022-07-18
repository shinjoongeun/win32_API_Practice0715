#pragma once
class CResource
{
private:
	wstring m_strKey;
	wstring m_strPath;

public:
	const wstring& GetKey() { return m_strKey; }
	const wstring& GetPath() { return m_strPath; }

	void SetKey(const wstring& _strKey)
	{
		m_strKey = _strKey;
	}
	void SetRelativePath(const wstring& _strRelativePath)
	{
		m_strPath = _strRelativePath;
	}

public:
	virtual int Load(const wstring& _strFilePath) = 0;

public:
	CResource();
	virtual ~CResource(); // ��� Resource Ŭ������ �θ� Ŭ������ �Ǵ� ���̱� ������ �Ҹ��ڸ� �����Լ��� �����Ѵ�.
};

