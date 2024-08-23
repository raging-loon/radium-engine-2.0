ess
Status dx12Device::init(RenderDeviceInitCfg cfg)
{
    assert(cfg.instance && cfg.windowHandle);

    m_cfg =
    {
        .windowHandle = cfg.windowHandle,
        .instance = cfg.instance
    };

#ifdef _DEBUG
    D3D12GetDebugInterface(IID_PPV_ARGS(m_dbgController.GetAddressOf()));
    m_dbgController->EnableDebugLayer();
#endif // _DEBUG

    HRESULT initStatus = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device));

    if (FAILED(initStatus))
        return ERR_UNSPECIFIED;

    return Status();
}

Status dx12Device::terminate()
{
    return Status();
}
