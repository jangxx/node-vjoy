import { vJoy } from "../";

console.log("vJoy Information");
console.log();
console.log(`Enabled: ${vJoy.isEnabled()}`);
console.log(`Version: ${vJoy.version()}`);
console.log(`Product: ${vJoy.productString()}`);
console.log(`Manufacturer: ${vJoy.manufacturerString()}`);
console.log(`Serial Number: ${vJoy.serialString()}`);

let match = vJoy.driverMatch();

console.log(`Driver version match: ${match.matches}`);
console.log(`SDK version:: ${match.dll_version}`);

console.log(`Max Devices: ${vJoy.maxDevices()}`);
console.log(`Current Devices: ${vJoy.existingDevices()}`);