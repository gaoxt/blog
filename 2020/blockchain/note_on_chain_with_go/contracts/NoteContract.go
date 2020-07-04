// Code generated - DO NOT EDIT.
// This file is a generated binding and any manual changes will be lost.

package contracts

import (
	"math/big"
	"strings"

	ethereum "github.com/ethereum/go-ethereum"
	"github.com/ethereum/go-ethereum/accounts/abi"
	"github.com/ethereum/go-ethereum/accounts/abi/bind"
	"github.com/ethereum/go-ethereum/common"
	"github.com/ethereum/go-ethereum/core/types"
	"github.com/ethereum/go-ethereum/event"
)

// Reference imports to suppress errors if they are not otherwise used.
var (
	_ = big.NewInt
	_ = strings.NewReader
	_ = ethereum.NotFound
	_ = bind.Bind
	_ = common.Big1
	_ = types.BloomLookup
	_ = event.NewSubscription
)

// NoteContractABI is the input ABI used to generate the binding from.
const NoteContractABI = "[{\"inputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"constructor\"},{\"anonymous\":false,\"inputs\":[{\"indexed\":false,\"internalType\":\"address\",\"name\":\"spender\",\"type\":\"address\"},{\"indexed\":false,\"internalType\":\"uint256\",\"name\":\"index\",\"type\":\"uint256\"}],\"name\":\"ModifyNote\",\"type\":\"event\"},{\"anonymous\":false,\"inputs\":[{\"indexed\":false,\"internalType\":\"address\",\"name\":\"spender\",\"type\":\"address\"},{\"indexed\":false,\"internalType\":\"string\",\"name\":\"note\",\"type\":\"string\"}],\"name\":\"NewNote\",\"type\":\"event\"},{\"inputs\":[{\"internalType\":\"string\",\"name\":\"note\",\"type\":\"string\"}],\"name\":\"addNote\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"own\",\"type\":\"address\"}],\"name\":\"getNotesLen\",\"outputs\":[{\"internalType\":\"uint256\",\"name\":\"\",\"type\":\"uint256\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"own\",\"type\":\"address\"},{\"internalType\":\"uint256\",\"name\":\"index\",\"type\":\"uint256\"},{\"internalType\":\"string\",\"name\":\"note\",\"type\":\"string\"}],\"name\":\"modifyNote\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"address\",\"name\":\"\",\"type\":\"address\"},{\"internalType\":\"uint256\",\"name\":\"\",\"type\":\"uint256\"}],\"name\":\"notes\",\"outputs\":[{\"internalType\":\"string\",\"name\":\"\",\"type\":\"string\"}],\"stateMutability\":\"view\",\"type\":\"function\"}]"

// NoteContractFuncSigs maps the 4-byte function signature to its string representation.
var NoteContractFuncSigs = map[string]string{
	"a4edff47": "addNote(string)",
	"787b582d": "getNotesLen(address)",
	"8766c0b8": "modifyNote(address,uint256,string)",
	"e0b117ff": "notes(address,uint256)",
}

// NoteContractBin is the compiled bytecode used for deploying new contracts.
var NoteContractBin = "0x608060405234801561001057600080fd5b506105f7806100206000396000f3fe608060405234801561001057600080fd5b506004361061004c5760003560e01c8063787b582d146100515780638766c0b814610089578063a4edff4714610146578063e0b117ff146101ec575b600080fd5b6100776004803603602081101561006757600080fd5b50356001600160a01b031661028d565b60408051918252519081900360200190f35b6101446004803603606081101561009f57600080fd5b6001600160a01b03823516916020810135918101906060810160408201356401000000008111156100cf57600080fd5b8201836020820111156100e157600080fd5b8035906020019184600183028401116401000000008311171561010357600080fd5b91908080601f0160208091040260200160405190810160405280939291908181526020018383808284376000920191909152509295506102a8945050505050565b005b6101446004803603602081101561015c57600080fd5b81019060208101813564010000000081111561017757600080fd5b82018360208201111561018957600080fd5b803590602001918460018302840111640100000000831117156101ab57600080fd5b91908080601f01602080910402602001604051908101604052809392919081815260200183838082843760009201919091525092955061038a945050505050565b6102186004803603604081101561020257600080fd5b506001600160a01b038135169060200135610472565b6040805160208082528351818301528351919283929083019185019080838360005b8381101561025257818101518382015260200161023a565b50505050905090810190601f16801561027f5780820380516001836020036101000a031916815260200191505b509250505060405180910390f35b6001600160a01b031660009081526020819052604090205490565b6001600160a01b03831633146102fc576040805162461bcd60e51b815260206004820152601460248201527336b7b234b33c9036bab9ba1031329037bbb732b960611b604482015290519081900360640190fd5b6001600160a01b038316600090815260208190526040902080548291908490811061032357fe5b906000526020600020019080519060200190610340929190610526565b50604080516001600160a01b03851681526020810184905281517f708dcbe9778aaa99c71e4a1412b2c9a5f0314a1deeaf46e51ecc48c46f11f1ec929181900390910190a1505050565b33600090815260208181526040822080546001810182559083529181902083516103bb939190910191840190610526565b507ff2555d00e065d582c4653357dbcf43cf8e0d291c35cc0faad6cf8467e8398c92338260405180836001600160a01b03166001600160a01b0316815260200180602001828103825283818151815260200191508051906020019080838360005b8381101561043457818101518382015260200161041c565b50505050905090810190601f1680156104615780820380516001836020036101000a031916815260200191505b50935050505060405180910390a150565b6000602052816000526040600020818154811061048b57fe5b600091825260209182902001805460408051601f6002600019610100600187161502019094169390930492830185900485028101850190915281815294509092509083018282801561051e5780601f106104f35761010080835404028352916020019161051e565b820191906000526020600020905b81548152906001019060200180831161050157829003601f168201915b505050505081565b828054600181600116156101000203166002900490600052602060002090601f016020900481019282601f1061056757805160ff1916838001178555610594565b82800160010185558215610594579182015b82811115610594578251825591602001919060010190610579565b506105a09291506105a4565b5090565b6105be91905b808211156105a057600081556001016105aa565b9056fea2646970667358221220727327733ec9cca4840badf10c028e4f86c2812860137071fc4c9ff5c731992b64736f6c634300060a0033"

// DeployNoteContract deploys a new Ethereum contract, binding an instance of NoteContract to it.
func DeployNoteContract(auth *bind.TransactOpts, backend bind.ContractBackend) (common.Address, *types.Transaction, *NoteContract, error) {
	parsed, err := abi.JSON(strings.NewReader(NoteContractABI))
	if err != nil {
		return common.Address{}, nil, nil, err
	}

	address, tx, contract, err := bind.DeployContract(auth, parsed, common.FromHex(NoteContractBin), backend)
	if err != nil {
		return common.Address{}, nil, nil, err
	}
	return address, tx, &NoteContract{NoteContractCaller: NoteContractCaller{contract: contract}, NoteContractTransactor: NoteContractTransactor{contract: contract}, NoteContractFilterer: NoteContractFilterer{contract: contract}}, nil
}

// NoteContract is an auto generated Go binding around an Ethereum contract.
type NoteContract struct {
	NoteContractCaller     // Read-only binding to the contract
	NoteContractTransactor // Write-only binding to the contract
	NoteContractFilterer   // Log filterer for contract events
}

// NoteContractCaller is an auto generated read-only Go binding around an Ethereum contract.
type NoteContractCaller struct {
	contract *bind.BoundContract // Generic contract wrapper for the low level calls
}

// NoteContractTransactor is an auto generated write-only Go binding around an Ethereum contract.
type NoteContractTransactor struct {
	contract *bind.BoundContract // Generic contract wrapper for the low level calls
}

// NoteContractFilterer is an auto generated log filtering Go binding around an Ethereum contract events.
type NoteContractFilterer struct {
	contract *bind.BoundContract // Generic contract wrapper for the low level calls
}

// NoteContractSession is an auto generated Go binding around an Ethereum contract,
// with pre-set call and transact options.
type NoteContractSession struct {
	Contract     *NoteContract     // Generic contract binding to set the session for
	CallOpts     bind.CallOpts     // Call options to use throughout this session
	TransactOpts bind.TransactOpts // Transaction auth options to use throughout this session
}

// NoteContractCallerSession is an auto generated read-only Go binding around an Ethereum contract,
// with pre-set call options.
type NoteContractCallerSession struct {
	Contract *NoteContractCaller // Generic contract caller binding to set the session for
	CallOpts bind.CallOpts       // Call options to use throughout this session
}

// NoteContractTransactorSession is an auto generated write-only Go binding around an Ethereum contract,
// with pre-set transact options.
type NoteContractTransactorSession struct {
	Contract     *NoteContractTransactor // Generic contract transactor binding to set the session for
	TransactOpts bind.TransactOpts       // Transaction auth options to use throughout this session
}

// NoteContractRaw is an auto generated low-level Go binding around an Ethereum contract.
type NoteContractRaw struct {
	Contract *NoteContract // Generic contract binding to access the raw methods on
}

// NoteContractCallerRaw is an auto generated low-level read-only Go binding around an Ethereum contract.
type NoteContractCallerRaw struct {
	Contract *NoteContractCaller // Generic read-only contract binding to access the raw methods on
}

// NoteContractTransactorRaw is an auto generated low-level write-only Go binding around an Ethereum contract.
type NoteContractTransactorRaw struct {
	Contract *NoteContractTransactor // Generic write-only contract binding to access the raw methods on
}

// NewNoteContract creates a new instance of NoteContract, bound to a specific deployed contract.
func NewNoteContract(address common.Address, backend bind.ContractBackend) (*NoteContract, error) {
	contract, err := bindNoteContract(address, backend, backend, backend)
	if err != nil {
		return nil, err
	}
	return &NoteContract{NoteContractCaller: NoteContractCaller{contract: contract}, NoteContractTransactor: NoteContractTransactor{contract: contract}, NoteContractFilterer: NoteContractFilterer{contract: contract}}, nil
}

// NewNoteContractCaller creates a new read-only instance of NoteContract, bound to a specific deployed contract.
func NewNoteContractCaller(address common.Address, caller bind.ContractCaller) (*NoteContractCaller, error) {
	contract, err := bindNoteContract(address, caller, nil, nil)
	if err != nil {
		return nil, err
	}
	return &NoteContractCaller{contract: contract}, nil
}

// NewNoteContractTransactor creates a new write-only instance of NoteContract, bound to a specific deployed contract.
func NewNoteContractTransactor(address common.Address, transactor bind.ContractTransactor) (*NoteContractTransactor, error) {
	contract, err := bindNoteContract(address, nil, transactor, nil)
	if err != nil {
		return nil, err
	}
	return &NoteContractTransactor{contract: contract}, nil
}

// NewNoteContractFilterer creates a new log filterer instance of NoteContract, bound to a specific deployed contract.
func NewNoteContractFilterer(address common.Address, filterer bind.ContractFilterer) (*NoteContractFilterer, error) {
	contract, err := bindNoteContract(address, nil, nil, filterer)
	if err != nil {
		return nil, err
	}
	return &NoteContractFilterer{contract: contract}, nil
}

// bindNoteContract binds a generic wrapper to an already deployed contract.
func bindNoteContract(address common.Address, caller bind.ContractCaller, transactor bind.ContractTransactor, filterer bind.ContractFilterer) (*bind.BoundContract, error) {
	parsed, err := abi.JSON(strings.NewReader(NoteContractABI))
	if err != nil {
		return nil, err
	}
	return bind.NewBoundContract(address, parsed, caller, transactor, filterer), nil
}

// Call invokes the (constant) contract method with params as input values and
// sets the output to result. The result type might be a single field for simple
// returns, a slice of interfaces for anonymous returns and a struct for named
// returns.
func (_NoteContract *NoteContractRaw) Call(opts *bind.CallOpts, result interface{}, method string, params ...interface{}) error {
	return _NoteContract.Contract.NoteContractCaller.contract.Call(opts, result, method, params...)
}

// Transfer initiates a plain transaction to move funds to the contract, calling
// its default method if one is available.
func (_NoteContract *NoteContractRaw) Transfer(opts *bind.TransactOpts) (*types.Transaction, error) {
	return _NoteContract.Contract.NoteContractTransactor.contract.Transfer(opts)
}

// Transact invokes the (paid) contract method with params as input values.
func (_NoteContract *NoteContractRaw) Transact(opts *bind.TransactOpts, method string, params ...interface{}) (*types.Transaction, error) {
	return _NoteContract.Contract.NoteContractTransactor.contract.Transact(opts, method, params...)
}

// Call invokes the (constant) contract method with params as input values and
// sets the output to result. The result type might be a single field for simple
// returns, a slice of interfaces for anonymous returns and a struct for named
// returns.
func (_NoteContract *NoteContractCallerRaw) Call(opts *bind.CallOpts, result interface{}, method string, params ...interface{}) error {
	return _NoteContract.Contract.contract.Call(opts, result, method, params...)
}

// Transfer initiates a plain transaction to move funds to the contract, calling
// its default method if one is available.
func (_NoteContract *NoteContractTransactorRaw) Transfer(opts *bind.TransactOpts) (*types.Transaction, error) {
	return _NoteContract.Contract.contract.Transfer(opts)
}

// Transact invokes the (paid) contract method with params as input values.
func (_NoteContract *NoteContractTransactorRaw) Transact(opts *bind.TransactOpts, method string, params ...interface{}) (*types.Transaction, error) {
	return _NoteContract.Contract.contract.Transact(opts, method, params...)
}

// GetNotesLen is a free data retrieval call binding the contract method 0x787b582d.
//
// Solidity: function getNotesLen(address own) view returns(uint256)
func (_NoteContract *NoteContractCaller) GetNotesLen(opts *bind.CallOpts, own common.Address) (*big.Int, error) {
	var (
		ret0 = new(*big.Int)
	)
	out := ret0
	err := _NoteContract.contract.Call(opts, out, "getNotesLen", own)
	return *ret0, err
}

// GetNotesLen is a free data retrieval call binding the contract method 0x787b582d.
//
// Solidity: function getNotesLen(address own) view returns(uint256)
func (_NoteContract *NoteContractSession) GetNotesLen(own common.Address) (*big.Int, error) {
	return _NoteContract.Contract.GetNotesLen(&_NoteContract.CallOpts, own)
}

// GetNotesLen is a free data retrieval call binding the contract method 0x787b582d.
//
// Solidity: function getNotesLen(address own) view returns(uint256)
func (_NoteContract *NoteContractCallerSession) GetNotesLen(own common.Address) (*big.Int, error) {
	return _NoteContract.Contract.GetNotesLen(&_NoteContract.CallOpts, own)
}

// Notes is a free data retrieval call binding the contract method 0xe0b117ff.
//
// Solidity: function notes(address , uint256 ) view returns(string)
func (_NoteContract *NoteContractCaller) Notes(opts *bind.CallOpts, arg0 common.Address, arg1 *big.Int) (string, error) {
	var (
		ret0 = new(string)
	)
	out := ret0
	err := _NoteContract.contract.Call(opts, out, "notes", arg0, arg1)
	return *ret0, err
}

// Notes is a free data retrieval call binding the contract method 0xe0b117ff.
//
// Solidity: function notes(address , uint256 ) view returns(string)
func (_NoteContract *NoteContractSession) Notes(arg0 common.Address, arg1 *big.Int) (string, error) {
	return _NoteContract.Contract.Notes(&_NoteContract.CallOpts, arg0, arg1)
}

// Notes is a free data retrieval call binding the contract method 0xe0b117ff.
//
// Solidity: function notes(address , uint256 ) view returns(string)
func (_NoteContract *NoteContractCallerSession) Notes(arg0 common.Address, arg1 *big.Int) (string, error) {
	return _NoteContract.Contract.Notes(&_NoteContract.CallOpts, arg0, arg1)
}

// AddNote is a paid mutator transaction binding the contract method 0xa4edff47.
//
// Solidity: function addNote(string note) returns()
func (_NoteContract *NoteContractTransactor) AddNote(opts *bind.TransactOpts, note string) (*types.Transaction, error) {
	return _NoteContract.contract.Transact(opts, "addNote", note)
}

// AddNote is a paid mutator transaction binding the contract method 0xa4edff47.
//
// Solidity: function addNote(string note) returns()
func (_NoteContract *NoteContractSession) AddNote(note string) (*types.Transaction, error) {
	return _NoteContract.Contract.AddNote(&_NoteContract.TransactOpts, note)
}

// AddNote is a paid mutator transaction binding the contract method 0xa4edff47.
//
// Solidity: function addNote(string note) returns()
func (_NoteContract *NoteContractTransactorSession) AddNote(note string) (*types.Transaction, error) {
	return _NoteContract.Contract.AddNote(&_NoteContract.TransactOpts, note)
}

// ModifyNote is a paid mutator transaction binding the contract method 0x8766c0b8.
//
// Solidity: function modifyNote(address own, uint256 index, string note) returns()
func (_NoteContract *NoteContractTransactor) ModifyNote(opts *bind.TransactOpts, own common.Address, index *big.Int, note string) (*types.Transaction, error) {
	return _NoteContract.contract.Transact(opts, "modifyNote", own, index, note)
}

// ModifyNote is a paid mutator transaction binding the contract method 0x8766c0b8.
//
// Solidity: function modifyNote(address own, uint256 index, string note) returns()
func (_NoteContract *NoteContractSession) ModifyNote(own common.Address, index *big.Int, note string) (*types.Transaction, error) {
	return _NoteContract.Contract.ModifyNote(&_NoteContract.TransactOpts, own, index, note)
}

// ModifyNote is a paid mutator transaction binding the contract method 0x8766c0b8.
//
// Solidity: function modifyNote(address own, uint256 index, string note) returns()
func (_NoteContract *NoteContractTransactorSession) ModifyNote(own common.Address, index *big.Int, note string) (*types.Transaction, error) {
	return _NoteContract.Contract.ModifyNote(&_NoteContract.TransactOpts, own, index, note)
}

// NoteContractModifyNoteIterator is returned from FilterModifyNote and is used to iterate over the raw logs and unpacked data for ModifyNote events raised by the NoteContract contract.
type NoteContractModifyNoteIterator struct {
	Event *NoteContractModifyNote // Event containing the contract specifics and raw log

	contract *bind.BoundContract // Generic contract to use for unpacking event data
	event    string              // Event name to use for unpacking event data

	logs chan types.Log        // Log channel receiving the found contract events
	sub  ethereum.Subscription // Subscription for errors, completion and termination
	done bool                  // Whether the subscription completed delivering logs
	fail error                 // Occurred error to stop iteration
}

// Next advances the iterator to the subsequent event, returning whether there
// are any more events found. In case of a retrieval or parsing error, false is
// returned and Error() can be queried for the exact failure.
func (it *NoteContractModifyNoteIterator) Next() bool {
	// If the iterator failed, stop iterating
	if it.fail != nil {
		return false
	}
	// If the iterator completed, deliver directly whatever's available
	if it.done {
		select {
		case log := <-it.logs:
			it.Event = new(NoteContractModifyNote)
			if err := it.contract.UnpackLog(it.Event, it.event, log); err != nil {
				it.fail = err
				return false
			}
			it.Event.Raw = log
			return true

		default:
			return false
		}
	}
	// Iterator still in progress, wait for either a data or an error event
	select {
	case log := <-it.logs:
		it.Event = new(NoteContractModifyNote)
		if err := it.contract.UnpackLog(it.Event, it.event, log); err != nil {
			it.fail = err
			return false
		}
		it.Event.Raw = log
		return true

	case err := <-it.sub.Err():
		it.done = true
		it.fail = err
		return it.Next()
	}
}

// Error returns any retrieval or parsing error occurred during filtering.
func (it *NoteContractModifyNoteIterator) Error() error {
	return it.fail
}

// Close terminates the iteration process, releasing any pending underlying
// resources.
func (it *NoteContractModifyNoteIterator) Close() error {
	it.sub.Unsubscribe()
	return nil
}

// NoteContractModifyNote represents a ModifyNote event raised by the NoteContract contract.
type NoteContractModifyNote struct {
	Spender common.Address
	Index   *big.Int
	Raw     types.Log // Blockchain specific contextual infos
}

// FilterModifyNote is a free log retrieval operation binding the contract event 0x708dcbe9778aaa99c71e4a1412b2c9a5f0314a1deeaf46e51ecc48c46f11f1ec.
//
// Solidity: event ModifyNote(address spender, uint256 index)
func (_NoteContract *NoteContractFilterer) FilterModifyNote(opts *bind.FilterOpts) (*NoteContractModifyNoteIterator, error) {

	logs, sub, err := _NoteContract.contract.FilterLogs(opts, "ModifyNote")
	if err != nil {
		return nil, err
	}
	return &NoteContractModifyNoteIterator{contract: _NoteContract.contract, event: "ModifyNote", logs: logs, sub: sub}, nil
}

// WatchModifyNote is a free log subscription operation binding the contract event 0x708dcbe9778aaa99c71e4a1412b2c9a5f0314a1deeaf46e51ecc48c46f11f1ec.
//
// Solidity: event ModifyNote(address spender, uint256 index)
func (_NoteContract *NoteContractFilterer) WatchModifyNote(opts *bind.WatchOpts, sink chan<- *NoteContractModifyNote) (event.Subscription, error) {

	logs, sub, err := _NoteContract.contract.WatchLogs(opts, "ModifyNote")
	if err != nil {
		return nil, err
	}
	return event.NewSubscription(func(quit <-chan struct{}) error {
		defer sub.Unsubscribe()
		for {
			select {
			case log := <-logs:
				// New log arrived, parse the event and forward to the user
				event := new(NoteContractModifyNote)
				if err := _NoteContract.contract.UnpackLog(event, "ModifyNote", log); err != nil {
					return err
				}
				event.Raw = log

				select {
				case sink <- event:
				case err := <-sub.Err():
					return err
				case <-quit:
					return nil
				}
			case err := <-sub.Err():
				return err
			case <-quit:
				return nil
			}
		}
	}), nil
}

// ParseModifyNote is a log parse operation binding the contract event 0x708dcbe9778aaa99c71e4a1412b2c9a5f0314a1deeaf46e51ecc48c46f11f1ec.
//
// Solidity: event ModifyNote(address spender, uint256 index)
func (_NoteContract *NoteContractFilterer) ParseModifyNote(log types.Log) (*NoteContractModifyNote, error) {
	event := new(NoteContractModifyNote)
	if err := _NoteContract.contract.UnpackLog(event, "ModifyNote", log); err != nil {
		return nil, err
	}
	return event, nil
}

// NoteContractNewNoteIterator is returned from FilterNewNote and is used to iterate over the raw logs and unpacked data for NewNote events raised by the NoteContract contract.
type NoteContractNewNoteIterator struct {
	Event *NoteContractNewNote // Event containing the contract specifics and raw log

	contract *bind.BoundContract // Generic contract to use for unpacking event data
	event    string              // Event name to use for unpacking event data

	logs chan types.Log        // Log channel receiving the found contract events
	sub  ethereum.Subscription // Subscription for errors, completion and termination
	done bool                  // Whether the subscription completed delivering logs
	fail error                 // Occurred error to stop iteration
}

// Next advances the iterator to the subsequent event, returning whether there
// are any more events found. In case of a retrieval or parsing error, false is
// returned and Error() can be queried for the exact failure.
func (it *NoteContractNewNoteIterator) Next() bool {
	// If the iterator failed, stop iterating
	if it.fail != nil {
		return false
	}
	// If the iterator completed, deliver directly whatever's available
	if it.done {
		select {
		case log := <-it.logs:
			it.Event = new(NoteContractNewNote)
			if err := it.contract.UnpackLog(it.Event, it.event, log); err != nil {
				it.fail = err
				return false
			}
			it.Event.Raw = log
			return true

		default:
			return false
		}
	}
	// Iterator still in progress, wait for either a data or an error event
	select {
	case log := <-it.logs:
		it.Event = new(NoteContractNewNote)
		if err := it.contract.UnpackLog(it.Event, it.event, log); err != nil {
			it.fail = err
			return false
		}
		it.Event.Raw = log
		return true

	case err := <-it.sub.Err():
		it.done = true
		it.fail = err
		return it.Next()
	}
}

// Error returns any retrieval or parsing error occurred during filtering.
func (it *NoteContractNewNoteIterator) Error() error {
	return it.fail
}

// Close terminates the iteration process, releasing any pending underlying
// resources.
func (it *NoteContractNewNoteIterator) Close() error {
	it.sub.Unsubscribe()
	return nil
}

// NoteContractNewNote represents a NewNote event raised by the NoteContract contract.
type NoteContractNewNote struct {
	Spender common.Address
	Note    string
	Raw     types.Log // Blockchain specific contextual infos
}

// FilterNewNote is a free log retrieval operation binding the contract event 0xf2555d00e065d582c4653357dbcf43cf8e0d291c35cc0faad6cf8467e8398c92.
//
// Solidity: event NewNote(address spender, string note)
func (_NoteContract *NoteContractFilterer) FilterNewNote(opts *bind.FilterOpts) (*NoteContractNewNoteIterator, error) {

	logs, sub, err := _NoteContract.contract.FilterLogs(opts, "NewNote")
	if err != nil {
		return nil, err
	}
	return &NoteContractNewNoteIterator{contract: _NoteContract.contract, event: "NewNote", logs: logs, sub: sub}, nil
}

// WatchNewNote is a free log subscription operation binding the contract event 0xf2555d00e065d582c4653357dbcf43cf8e0d291c35cc0faad6cf8467e8398c92.
//
// Solidity: event NewNote(address spender, string note)
func (_NoteContract *NoteContractFilterer) WatchNewNote(opts *bind.WatchOpts, sink chan<- *NoteContractNewNote) (event.Subscription, error) {

	logs, sub, err := _NoteContract.contract.WatchLogs(opts, "NewNote")
	if err != nil {
		return nil, err
	}
	return event.NewSubscription(func(quit <-chan struct{}) error {
		defer sub.Unsubscribe()
		for {
			select {
			case log := <-logs:
				// New log arrived, parse the event and forward to the user
				event := new(NoteContractNewNote)
				if err := _NoteContract.contract.UnpackLog(event, "NewNote", log); err != nil {
					return err
				}
				event.Raw = log

				select {
				case sink <- event:
				case err := <-sub.Err():
					return err
				case <-quit:
					return nil
				}
			case err := <-sub.Err():
				return err
			case <-quit:
				return nil
			}
		}
	}), nil
}

// ParseNewNote is a log parse operation binding the contract event 0xf2555d00e065d582c4653357dbcf43cf8e0d291c35cc0faad6cf8467e8398c92.
//
// Solidity: event NewNote(address spender, string note)
func (_NoteContract *NoteContractFilterer) ParseNewNote(log types.Log) (*NoteContractNewNote, error) {
	event := new(NoteContractNewNote)
	if err := _NoteContract.contract.UnpackLog(event, "NewNote", log); err != nil {
		return nil, err
	}
	return event, nil
}
