#pragma once
#include "GameUtil.h"
#include "GameTimer.h"

class GameApp 
{
public:
	GameApp(HINSTANCE hInstance,std::wstring appTitle);
	GameApp(const GameApp& rhs) = delete;
	GameApp& operator=(const GameApp& rhs) = delete;
	virtual ~GameApp();

	HINSTANCE AppInst()const;
	HWND      MainWnd()const;
	float     AspectRatio()const;

	bool Get4xMsaaState()const;
	void Set4xMsaaState(bool value);

	int Run();

	virtual bool Initialize();
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	virtual void CreateRtvAndDsvDescriptorHeaps();
	virtual void OnResize();
	virtual void Update(const GameTimer& gt) = 0;
	virtual void Render(const GameTimer& gt) = 0;

	// Convenience overrides for handling mouse input.
	virtual void OnMouseDown(WPARAM btnState, int x, int y) { }
	virtual void OnMouseUp(WPARAM btnState, int x, int y) { }
	virtual void OnMouseMove(WPARAM btnState, int x, int y) { }

	bool InitMainWindow();
	bool InitDirect3D();
	void CreateCommandObjects();
	void CreateSwapChain();

	void FlushCommandQueue();

	ID3D12Resource* CurrentBackBuffer()const;
	D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView()const;
	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView()const;

	void CalculateFrameStats();

	void LogAdapters();
	void LogAdapterOutputs(IDXGIAdapter* adapter);
	void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);

	Microsoft::WRL::ComPtr<IDXGIFactory4> mdxgiFactory;
	Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
	Microsoft::WRL::ComPtr<ID3D12Device> md3dDevice;
	Microsoft::WRL::ComPtr<ID3D12Fence> mFence;
	
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> mCommandQueue;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> mDirectCmdListAlloc;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mCommandList;

	
	static const int SwapChainBufferCount = 2;
	Microsoft::WRL::ComPtr<ID3D12Resource> mSwapChainBuffer[SwapChainBufferCount];
	Microsoft::WRL::ComPtr<ID3D12Resource> mDepthStencilBuffer;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mRtvHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mDsvHeap;

	static GameApp* GetApp() { return mApp; }
protected:
	D3D12_RECT		mScissorRect;
	D3D12_VIEWPORT	mScreenViewport;
	UINT			mCurrBackBuffer;
	HWND			mhMainWnd;				//main window handle
	DXGI_FORMAT		mBackBufferFormat;		//DXGI_FORMAT_R8G8B8A8_UNORM;
	DXGI_FORMAT		mDepthStencilFormat;	//DXGI_FORMAT_D24_UNORM_S8_UINT;
	
	// Set true to use 4X MSAA.  The default is false.
	UINT			m4xMsaaQuality;			// quality level of 4X MSAA
	bool			m4xMsaaState;			// 4X MSAA enabled

private:
	GameTimer		mTimer;
	static GameApp* mApp;
	
	UINT64			mCurrentFence;
	int				mClientWidth;
	int				mClientHeight;
	UINT			mRtvDescriptorSize;
	UINT			mDsvDescriptorSize;
	UINT			mCbvSrvUavDescriptorSize;
	D3D_DRIVER_TYPE md3dDriverType;

	std::wstring	mMainWndCaption;

	HINSTANCE		mhAppInst;				// application instance handle
	
	bool			mAppPaused;				// is the application paused?
	bool			mMinimized;				// is the application minimized?
	bool			mMaximized;				// is the application maximized?
	bool			mResizing;				// are the resize bars being dragged?
	bool			mFullscreenState;		// fullscreen enabled

};