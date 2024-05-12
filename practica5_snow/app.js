/* eslint-disable no-unused-vars */
import { ByteMultiplier } from "./bitmultiplicado.js";


const snow3g = new ByteMultiplier(0xa9);
const aes = new ByteMultiplier(0x1b);

Number.prototype.toBinaryByte = function () {
  return this.toString(2).padStart(8, '0');
};

function getMultiplicand(algorithm) {
  const multiplicand = parseInt(document.getElementById(algorithm + '-multiplicand').value, 16);
  return multiplicand;
}

function getMultiplier(algorithm) {
  const multiplier = parseInt(document.getElementById(algorithm + '-multiplier').value, 16);
  return multiplier;
}

function getProduct(algorithm) {
  const product = document.getElementById(algorithm + '-product').value;
  return product;
}

function getBinaryMultiplier(algorithm) {
  const binaryMultiplier = document.getElementById(algorithm + '-binary-multiplier').value;
  return binaryMultiplier;
}
function getBinaryMultiplicand(algorithm) {
  const binaryMultiplicand = document.getElementById(algorithm + '-binary-multiplicand').value;
  return binaryMultiplicand;
}

function getCustomAlgorithmByte() {
  const customAlgorithmByte = parseInt(document.getElementById('custom-algorithm-byte').value, 16);
  return customAlgorithmByte;
}


function setCustomAlgorithmByte(customAlgorithmByte) {
  document.getElementById('custom-algorithm-byte').value = `0x${customAlgorithmByte.toString(16).padStart(2, '0')}`;
}

function setBinaryMultiplicand(algorithm) {
  document.getElementById(algorithm + '-binary-multiplicand').value = getMultiplicand(algorithm).toBinaryByte();
}

function setBinaryMultiplier(algorithm) {
  document.getElementById(algorithm + '-binary-multiplier').value = getMultiplier(algorithm).toBinaryByte();
}

function setProduct(algorithm, product) {
  document.getElementById(algorithm + '-product').value = `0x${product.toString(16).padStart(2, '0')}`;
}

function setBinaryProduct(algorithm) {
  document.getElementById(algorithm + '-binary-product').value = parseInt(getProduct(algorithm), 16).toString(2).padStart(8, '0');
}

function setMainLog(algorithm, multiplier) {
  const mainLog = document.getElementById(algorithm + '-mainlog');
  mainLog.value = '';

  const results = [...multiplier.mainLog.results];

  multiplier.mainLog.factors.forEach((factor, index) => {
    mainLog.value += `${index.toString().padStart(2, '0')}  ${getBinaryMultiplicand(algorithm)}    *    ${factor.toBinaryByte()}    =     ${results[index].toBinaryByte()}\n`;
  });
  mainLog.value += `                                                          ___________\n`;
  mainLog.value += `                                                          ${parseInt(getProduct(algorithm), 16).toBinaryByte()}`;
}

function setSubLog(algorithm, multiplier) {
  const subLog = document.getElementById(algorithm + '-sublog');
  subLog.value = '';

  multiplier.subLog.forEach((l, i) => {
    subLog.value += `\n${(i + 1).toString().padStart(2, '0')}:\n`;
    subLog.value += `  00: ${l[0]}\n`;
    l.slice(1).forEach((m, j) => {
      subLog.value += `  ${(j + 1).toString().padStart(2, '0')}: ${m.operation} ${m.result}\n`;
    });
  });
}

function calculate(algorithm = 'snow3g') {
  let multiplier;
  if (algorithm === 'snow3g') {
    multiplier = snow3g;
  } else if (algorithm === 'aes') {
    multiplier = aes;
  } else {
    const customAlgorithmByte = getCustomAlgorithmByte();
    setCustomAlgorithmByte(customAlgorithmByte);
    multiplier = new ByteMultiplier(customAlgorithmByte);
  }

  const product = multiplier.multiply(getMultiplicand(algorithm), getMultiplier(algorithm));
  setProduct(algorithm, product);

  setBinaryMultiplicand(algorithm);
  setBinaryMultiplier(algorithm);
  setBinaryProduct(algorithm);

  setMainLog(algorithm, multiplier);
  setSubLog(algorithm, multiplier);

}


// Pruebas

const multiplier = new ByteMultiplier(0x1b);
console.log('- AES cb * 19:');
console.log('First: ', multiplier.multiplyByFactor(0xcb, 0x19).toString(2).padStart(8, '0'));
console.log('Decomposition cb: ', multiplier.decomposeByte(0xcb));
console.log('Decomposition 19: ', multiplier.decomposeByte(0x19));
console.log('Multiplication 57 x 83: ', multiplier.multiply(0x57, 0x83).toString(2).padStart(8, '0'));

console.log('- Snow3g cb * 19:');
console.log('Multiplication cb * 19: ', new ByteMultiplier(0xA9).multiply(0xcb, 0x19).toString(2).padStart(8, '0'));

let multiplicand = '01010111';
let multiplier_ = '00000010';

console.log(multiplier.multiplyByFactor(parseInt(multiplicand, 2), parseInt(multiplier_, 2)).toString(2).padStart(8, '0'));
let result = multiplier.multiply(parseInt(multiplicand, 2), parseInt(multiplier_, 2));
console.log(`${multiplicand} * ${multiplier_} = ${result.toString(2).padStart(8, '0')}`);

multiplicand = '10101100';
multiplier_ = '00000011';
result = multiplier.multiply(parseInt(multiplicand, 2), parseInt(multiplier_, 2));
console.log(`${multiplicand} * ${multiplier_} = ${result.toString(2).padStart(8, '0')}`);

// window.calculate = calculate;
// window.multiplier = snow3g;
// // Exporta la función calculate para que pueda ser importada en otros archivos
export { calculate };

// // También puedes exportar otros objetos o funciones según sea necesario
export { snow3g, aes }; // Por ejemplo, si necesitas exportar lo


