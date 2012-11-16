
#include "Stdafx.h"
#include "tier0\memalloc.h"
#include "crtdbg.h"

class CMemAlloc : public IMemAlloc
{
public:
		// Release versions
	virtual void *Alloc( size_t nSize )
	{
		return malloc(nSize);
	}

	virtual void *Realloc( void *pMem, size_t nSize )
	{
		return realloc(pMem, nSize);
	}

	virtual void Free( void *pMem )
	{
		return free(pMem);
	}

    virtual void *Expand_NoLongerSupported( void *pMem, size_t nSize )
	{
		return realloc(pMem, nSize);
	}

	// Debug versions
    virtual void *Alloc( size_t nSize, const char *pFileName, int nLine )
	{
		return malloc(nSize);
	}

    virtual void *Realloc( void *pMem, size_t nSize, const char *pFileName, int nLine )
	{
		return realloc(pMem, nSize);
	}

    virtual void  Free( void *pMem, const char *pFileName, int nLine )
	{
		return free(pMem);
	}

    virtual void *Expand_NoLongerSupported( void *pMem, size_t nSize, const char *pFileName, int nLine )
	{
		return realloc(pMem, nSize);
	}

	// Returns size of a particular allocation
	virtual size_t GetSize( void *pMem )
	{
		return sizeof(pMem);
	}

    // Force file + line information for an allocation
	virtual void PushAllocDbgInfo( const char *pFileName, int nLine ){}
    virtual void PopAllocDbgInfo(){}

	// FIXME: Remove when we have our own allocator
	// these methods of the Crt debug code is used in our codebase currently
	virtual long CrtSetBreakAlloc( long lNewBreakAlloc )
	{
		return 0;
	}

	virtual	int CrtSetReportMode( int nReportType, int nReportMode )
	{
		return 0;
	}

	virtual int CrtIsValidHeapPointer( const void *pMem )
	{
		return 0;
	}

	virtual int CrtIsValidPointer( const void *pMem, unsigned int size, int access )
	{
		return 0;
	}

	virtual int CrtCheckMemory( void )
	{
		return 0;
	}

	virtual int CrtSetDbgFlag( int nNewFlag ) 
	{
		return 0;
	}

	virtual void CrtMemCheckpoint( _CrtMemState *pState ){}

	// FIXME: Make a better stats interface
	virtual void DumpStats(){}
	virtual void DumpStatsFileBase( char const *pchFileBase ){}

	// FIXME: Remove when we have our own allocator
	virtual void* CrtSetReportFile( int nRptType, void* hFile )
	{
		return 0;
	}

	virtual void* CrtSetReportHook( void* pfnNewHook )
	{
		return 0;
	}

	virtual int CrtDbgReport( int nRptType, const char * szFile, int nLine, const char * szModule, const char * pMsg )
	{
		return 0;
	}

	virtual int heapchk()
	{
		return 0;
	}

	virtual bool IsDebugHeap()
	{
		return true;
	}

	virtual void GetActualDbgInfo( const char *&pFileName, int &nLine ){}
	virtual void RegisterAllocation( const char *pFileName, int nLine, int nLogicalSize, int nActualSize, unsigned nTime ){}
	virtual void RegisterDeallocation( const char *pFileName, int nLine, int nLogicalSize, int nActualSize, unsigned nTime ){}

	virtual int GetVersion()
	{
		return 0;
	}

	virtual void CompactHeap(){}

	// Function called when malloc fails or memory limits hit to attempt to free up memory (can come in any thread)
	virtual MemAllocFailHandler_t SetAllocFailHandler( MemAllocFailHandler_t pfnMemAllocFailHandler )
	{
		return nullptr;
	}

	virtual void DumpBlockStats( void * ) {}

#if defined( _MEMTEST )	
	virtual void SetStatsExtraInfo( const char *pMapName, const char *pComment ) = 0;
#endif

	// Returns 0 if no failure, otherwise the size_t of the last requested chunk
	virtual size_t MemoryAllocFailed()
	{
		return 0;
	}
};


IMemAlloc *g_pMemAlloc = new CMemAlloc();
