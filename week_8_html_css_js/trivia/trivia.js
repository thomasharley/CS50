document.addEventListener('DOMContentLoaded', function() {

    let corrects = document.querySelectorAll(".correct");
    let incorrects = document.querySelectorAll(".incorrect");
    let form = document.querySelector("#form");

    /** if you select correct answer */
    for (let i = 0; i<corrects.length; i++) {
        /** create selector for each correct */
        corrects[i].addEventListener('click', function() {
            resetButtons();
            Correct(corrects[i]);
        });
    }

    /** if you select incorrect answer */
    for (let i = 0; i<incorrects.length; i++) {
        /** create selector for each incorrect */
        incorrects[i].addEventListener('click', function() {
            resetButtons();
            InCorrect(incorrects[i]);
        });
    }

    document.querySelector("#check").addEventListener('click', function() {
        if(form.value == "Switzerland") {
            Correct(form);
        }
        else {
            InCorrect(form);
        }
    });

});

function resetButtons() {
    let buttons = document.querySelectorAll(".correct, .incorrect");
    for (let i = 0; i<buttons.length; i++) {
        buttons[i].style.backgroundColor = '#d9edff'
    }
}

function Correct(correct) {
    /** set background colour to green */ 
    correct.style.backgroundColor = 'Green';
    /** print out correct */
    correct.parentElement.querySelector('.feedback').innerHTML = 'Correct!';
}

function InCorrect(incorrect) {
    /** set background colour to green */ 
    incorrect.style.backgroundColor = 'Red';
    /** print out incorrect */
    incorrect.parentElement.querySelector('.feedback').innerHTML = 'Incorrect! Try Again!';
}