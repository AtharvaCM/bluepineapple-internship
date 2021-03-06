// Create a function that takes an array of strings and returns an array
// with only the strings that have numbers in them. If there are no strings
// containing numbers, return an empty array.

function stringContainsNumber(inputString) {
  let string = inputString;

  for (let i = 0; i < string.length; i++) {
    // JavaScript interprets an empty string as a 0, which then fails the isNAN test
    if (!isNaN(string.charAt(i)) && !(string.charAt(i) === " ")) {
      return true;
    }
  }

  return false;
}

function getStringsContainingNumbers(inputArray) {
  let resultArray = [];

  inputArray.forEach((element) => {
    if (stringContainsNumber(element)) {
      resultArray.push(element);
    }
  });

  return resultArray;
}

const inputArray = ["hellow", "world", "shade45", "9to5", "react is awesome"];

let result = getStringsContainingNumbers(inputArray);
console.log(result);
