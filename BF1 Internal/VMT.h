

class CVMTHookManager64
{
public:
	CVMTHookManager64(void)
	{
		memset(this, 0, sizeof(CVMTHookManager64));
	}

	template <class vType>
	CVMTHookManager64(vType ppdwClassBase)
	{
		bInitialize((QWORD**)ppdwClassBase);
	}

	~CVMTHookManager64(void)
	{
		UnHook();
	}

	bool bInitialize(PDWORD64* ppdwClassBase)
	{
		m_ppdwClassBase = ppdwClassBase;
		m_pdwOldVMT = *ppdwClassBase;
		m_dwVMTSize = dwGetVMTCount(*ppdwClassBase);
		m_pdwNewVMT = new DWORD64[m_dwVMTSize];
		memcpy(m_pdwNewVMT, m_pdwOldVMT, sizeof(DWORD64) * m_dwVMTSize);
		*ppdwClassBase = m_pdwNewVMT;
		return true;
	}

	bool bInitialize(PDWORD64** pppdwClassBase)
	{
		return bInitialize(*pppdwClassBase);
	}
	void UnHook(void)
	{
		m_pdwNewVMT[unhookindex] = oFunction;
	}

	void ReHook(void)
	{
		if (m_ppdwClassBase)
		{
			*m_ppdwClassBase = m_pdwNewVMT;
		}
	}

	int iGetFuncCount(void)
	{
		return(int)m_dwVMTSize;
	}

	DWORD64 dwGetMethodAddress(int Index)
	{
		if (Index >= 0 && Index <= (int)m_dwVMTSize && m_pdwOldVMT != NULL)
		{
			oFunction = m_pdwOldVMT[Index];
			unhookindex = Index;
			return m_pdwOldVMT[Index];
		}
	}

	PDWORD64 pdwGetOldVMT(void)
	{
		return m_pdwOldVMT;
	}

	QWORD dwHookMethod(DWORD64 dwNewFunc, unsigned int iIndex)
	{
		if (m_pdwNewVMT && m_pdwOldVMT && iIndex <= m_dwVMTSize && iIndex >= 0)
		{
			oFunction = m_pdwOldVMT[iIndex];
			unhookindex = iIndex;
			m_pdwNewVMT[iIndex] = dwNewFunc;
			return m_pdwOldVMT[iIndex];
		}
		return NULL;
	}

	template <class vfType>
	vfType dwHookMethod(DWORD64 dwNewFunc, unsigned int iIndex)
	{
		if (m_pdwNewVMT && m_pdwOldVMT &&iIndex <= m_dwVMTSize&&iIndex >= 0)
		{
			m_pdwNewVMT[iIndex] = dwNewFunc;
			return reinterpret_cast<vfType>(m_pdwOldVMT[iIndex]);
		}
		return NULL;
	}
private:
	DWORD64 dwGetVMTCount(PDWORD64 pdwVMT)
	{
		DWORD dwIndex = 0;
		for (dwIndex = 0;pdwVMT[dwIndex];dwIndex++)
		{
			if (!Mem::IsValid((PVOID)pdwVMT[dwIndex]))
				break;
		}
		return dwIndex;
	}

	PDWORD64* m_ppdwClassBase;
	PDWORD64 m_pdwNewVMT, m_pdwOldVMT;
	DWORD64 m_dwVMTSize, oFunction;
	int unhookindex;
};