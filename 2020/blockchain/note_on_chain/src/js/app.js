var App = {
  web3Provider: null,
  contracts: {},

  init: async function () {
    return await App.initWeb3();
  },

  initWeb3: async function () {
    // Modern dapp browsers...
    if (window.ethereum) {
      App.web3Provider = window.ethereum;
      try {
        // Request account access
        await window.ethereum.enable();
      } catch (error) {
        // User denied account access...
        console.error("User denied account access")
      }
    }
    // Legacy dapp browsers...
    else if (window.web3) {
      App.web3Provider = window.web3.currentProvider;
    }
    // If no injected web3 instance is detected, fall back to Ganache
    else {
      App.web3Provider = new Web3.providers.HttpProvider('http://localhost:7545');
    }
    web3 = new Web3(App.web3Provider);

    return App.initContract();
  },

  initContract: function () {
    $.getJSON('NoteContract.json', function (data) {
      App.contracts.noteContract = TruffleContract(data);
      App.contracts.noteContract.setProvider(App.web3Provider);

      App.contracts.noteContract.deployed().then(function (instance) {
        App.noteIntance = instance;
        App.getNotes();
      });
    });

    web3.eth.getAccounts(function (error, accounts) {
      if (error) {
        console.log(error);
      }
      var account = accounts[0];
      App.account = account
    });

    App.currentIndex = 0
    return App.bindEvents();
  },

  loadNote: function (index) {
    App.noteIntance.notes(App.account, index).then(function (note) {
      $("#notes").append(createHtmlTemplate(index, note));
      if (index - 1 >= 0) {
        App.loadNote(index - 1);
      }
    }).catch(function (err) {
    });
  },

  getNotes: function () {
    App.noteIntance.getNotesLen(App.account).then(function (len) {
      App.noteLength = len;
      if (len > 0) {
        App.loadNote(len - 1);
      }
    }).catch(function (err) {
      console.log(err);
    });
  },

  addNotes: function (btn) {
    if ($("#new_note").val() == '') {
      return;
    }
    btn.button('loading');
    App.noteIntance.addNote($("#new_note").val()).then(function (result) {
      $("#notes").prepend(createHtmlTemplate(App.noteLength, $("#new_note").val()));
      $("#new_note").val('')
    }).catch(function (err) {
      console.log(err);
    }).finally(function () {
      btn.button('reset')
    });
  },

  updateNotes: function (btn) {
    btn.button('loading')
    App.noteIntance.modifyNote(App.account, App.currentIndex, $('#modify_note').val()).then(function () {
      $('.index_' + App.currentIndex).text($('#modify_note').val())
      $('#modify-model').modal('hide')
    }).catch(function (err) {
      console.log(err);
    }).finally(function () {
      btn.button('reset')
    });
  },

  bindEvents: function () {
    $("#add_new").on('click', function (e) {
      App.addNotes($(this))
      return;
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
