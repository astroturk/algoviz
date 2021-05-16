// Run Terminal Animation on Heading upon Loading
document.addEventListener('DOMContentLoaded', consoleText('AlgoViz.', 'text'), false);

function consoleText(word, id) {
  var visible = true;
  var con = document.getElementById('console');
  var letterCount = 1;
  var target = document.getElementById(id)
  
  const interval = window.setInterval(function() {
    if (letterCount === word.length + 1) {
      clearInterval(interval)
      }
    else{
      target.innerHTML = word.substring(0, letterCount)
      letterCount++;
    }
  }, 150)
  
  window.setInterval(function() {
    if (visible === true) {
      con.className = 'console-underscore hidden'
      visible = false;

    } else {
      con.className = 'console-underscore'
      visible = true;
    }
  }, 400)
}

// Extracting ipcRenderer from  window.ipcRenderer
const ipcRenderer = window.ipcRenderer

// Alert Sign
const alert = document.getElementById('codeEditorAlert')


ipcRenderer.on('code-compiled', (event, arg) => {
  console.log("Recieved Stdout")
  console.log(arg)
  alert.className = "alert alert-success"
  alert.innerHTML = "Code Compiled Successfully!"

  /*console.log('Clearing Algorithm Viewer Division')
  const av = document.getElementById('divAv')
  av.innerHTML = '<div id="av"></div>'*/

  console.log("Clearing out variable Used")
  for (var i = 0; i < variablesUsed.length; i++){
    console.log(variablesUsed[i])
    const clearCmd = `${variablesUsed[i]}.clear()`
    const assignCmd = `${variablesUsed[i]}=undefined`
    const deleteCmd = `delete(${variablesUsed[i]})`
    eval(clearCmd)
    eval(assignCmd)
    eval(deleteCmd)
    //console.log(assignCmd, deleteCmd)
  }
  console.log("Variables Cleared")
  variablesUsed = []

  const data = JSON.parse(arg)
  console.log(data.var)

  variablesUsed = data.var
  console.log(data.code)
  const commands = data.code.split(';')
  console.log(commands)
  //console.log("stdout Recieved:", arg)
  for (var i = 0; i < commands.length - 1; i++){
    eval(commands[i])
  }
})

ipcRenderer.on('code-not-compiled', (event, arg) => {
  alert.className = "alert alert-danger"
  alert.innerHTML = "Some Error Occurred"
  console.log("Error:", arg)
})

const submitButton = document.getElementById('codeEditorSubmit')
submitButton.addEventListener('click', () => {
  alert.className = "alert alert-light"
  alert.innerHTML = "Loading..."

  var value = window.editor.getValue()
  console.log(value)

  console.log('Sending Code to Main Process')
  ipcRenderer.send('insert-compile-code', value);
})