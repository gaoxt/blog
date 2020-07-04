var App = {
  contracts: {},

  init: async function () {
    App.currentIndex = 0
    App.noteLength = 0
    App.loadNote()
    App.bindEvents();
  },

  loadNote: async function () {
    var result = await fetch('/list')
      .then(response => response.json())
      .catch(error => console.error('Error:', error))

    if (result.code == 200) {
      let list = result.data.reverse();
      App.noteLength = list.length
      list.forEach((note, index) => {
        $("#notes").append(createHtmlTemplate(list.length - index - 1, note));
      });
    }
  },

  addNotes: async function (btn) {
    if ($("#new_note").val() == '') {
      return;
    }
    btn.button('loading');
    var result = await fetch('/add', {
      headers: { 'content-type': 'application/json' },
      method: 'POST',
      body: JSON.stringify({
        note: $("#new_note").val()
      })
    })
      .then(response => response.json())
      .catch(error => console.error('Error:', error))
    if (result.code == 200) {
      $("#notes").prepend(createHtmlTemplate(App.noteLength, $("#new_note").val()));
      $("#new_note").val('')
    }
  },

  updateNotes: async function (btn) {
    btn.button('loading')
    var result = await fetch('/update', {
      headers: { 'content-type': 'application/json' },
      method: 'POST',
      body: JSON.stringify({ index: String(App.currentIndex), note: $('#modify_note').val() })
    })
      .then(response => response.json())
      .catch(error => console.error('Error:', error))
    if (result.code == 200) {
      $('.index_' + App.currentIndex).text($('#modify_note').val())
      $('#modify-model').modal('hide')
    }
    btn.button('reset')
  },


  bindEvents: function () {
    $("#add_new").on('click', function () {
      App.addNotes($(this))
    });
    $('#modify-model').on('show.bs.modal', function (event) {
      App.currentIndex = $(event.relatedTarget).data('index');
      $('#modify_note').val($(event.relatedTarget).find('p')[0].innerText)
    });
    $('#change').on('click', function () {
      App.updateNotes($(this))
    })
  }

};

function createHtmlTemplate(index, note) {
  return '<a href="#" class="list-group-item index_' + index + '" data-index="' + index + '" data-toggle="modal" data-target="#modify-model"><p class="list-group-item-text">' + note + '</p></a>'
}

$(function () {
  $(window).load(function () {
    App.init();
  });
});
