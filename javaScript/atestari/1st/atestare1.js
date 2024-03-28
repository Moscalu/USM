const fieldsValueCounter = document.getElementById('calorie-counter');
const fieldsInput = document.getElementById('budget');
const addEntryButton = document.getElementById('add-entry');
const clearButton = document.getElementById('clear');
const output = document.getElementById('output');
let isError = false;

function cleanInputString(str) {
  const regex = /[+-\s]/g;
  return str.replace(regex, '');
}

function isInvalidInput(str) {
  const regex = /\d+e\d+/i;
  return str.match(regex);
}

function addEntry() {
  //const targetInputContainer = document.querySelector(`#${entryDropdown.value} .input-container`);
  const targetInputContainer = document.querySelector('#raw .input-container')
  const entryNumber = targetInputContainer.querySelectorAll('input[type="number"]').length + 1;
  const HTMLString = `
  <label for="raw-${entryNumber}-value">Entry ${entryNumber} Value</label>
  <input
    type="number"
    min="0"
    id="raw-${entryNumber}-value"
    placeholder="Value"
  /><br>`;
  targetInputContainer.insertAdjacentHTML('beforeend', HTMLString);
}

function calculateValues(e) {
  e.preventDefault();
  isError = false;

  const rawNumberInputs = document.querySelectorAll('#raw input[type=number]');
  const rawValues = getCaloriesFromInputs(rawNumberInputs);

  if (isError) {
    return;
  }

  const rawValuesSum = rawValues;
  output.innerHTML = `<p>Sum of current fields is: ${rawValuesSum}</p>`;
  output.classList.remove('hide');
}

function getCaloriesFromInputs(list) {
  let calories = 0;

  for (const item of list) {
    const currVal = cleanInputString(item.value);
    const invalidInputMatch = isInvalidInput(currVal);

    if (invalidInputMatch) {
      alert(`Invalid Input: ${invalidInputMatch[0]}`);
      isError = true;
      return null;
    }
    calories += Number(currVal);
  }
  return calories;
}

function clearForm() {
  const inputContainers = Array.from(document.querySelectorAll('.input-container'));

  for (const container of inputContainers) {
    container.innerHTML = '';
  }

  fieldsInput.value = '';
  output.innerText = '';
  output.classList.add('hide');

}

addEntryButton.addEventListener("click", addEntry);
fieldsValueCounter.addEventListener("submit", calculateValues);
clearButton.addEventListener("click", clearForm);