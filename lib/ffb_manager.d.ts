declare const _exports: FFBManager;
export = _exports;
declare class FFBManager {
    _registeredCallbacks: {};
    _driverRegistered: boolean;
    _handleEvent(deviceId: any, evt: any): void;
    register(deviceId: any, callback: any): void;
    unregister(deviceId: any): void;
}
