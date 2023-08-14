declare class FFBManager {
    register(deviceId: number, callback: any): void;
    unregister(deviceId: number): void;
}

declare const _exports: FFBManager;
export = _exports;