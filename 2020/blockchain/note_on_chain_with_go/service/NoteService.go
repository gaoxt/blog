package service

import (
	"log"
	"math/big"
	"note_on_chain_with_go/contracts"

	"github.com/ethereum/go-ethereum/accounts/abi/bind"
	"github.com/ethereum/go-ethereum/common"
	"github.com/ethereum/go-ethereum/core/types"
	"github.com/ethereum/go-ethereum/crypto"
	"github.com/ethereum/go-ethereum/ethclient"
)

type NoteContract struct {
	contract        *contracts.NoteContract
	NoteLen         int64
	contractAddress common.Address
	accountAddress  common.Address
}

func NewNoteContract() *NoteContract {
	c := new(NoteContract)
	c.accountAddress = common.HexToAddress("0x97AF9124a95639ded09CF337D1EcB07D3B36e259")
	c.contractAddress = common.HexToAddress("0xc143cE0ab6Fc8F2140A1C2382CB0B7629972b942")
	client, err := ethclient.Dial("http://127.0.0.1:7545")
	if err != nil {
		log.Fatalf("could not connect to Ethereum gateway: %v\n", err)
	}
	contract, err := contracts.NewNoteContract(c.contractAddress, client)
	if err != nil {
		log.Fatalf("conn contract: %v \n", err)
	}
	c.contract = contract
	c.GetNoteLen()
	return c
}

func accountAuth() *bind.TransactOpts {
	privateKey, err := crypto.HexToECDSA("a6a1d2b6d8972d5b12b87e976822fb52f6fd8b2e6280ad69a94ea70ca16330a6")
	if err != nil {
		log.Fatal(err)
	}
	return bind.NewKeyedTransactor(privateKey)
}

func (c *NoteContract) GetNoteLen() {
	noteLen, err := c.contract.GetNotesLen(nil, c.accountAddress)
	if err != nil {
		log.Fatalf("getNoteLen: %v \n", err)
	}
	c.NoteLen = noteLen.Int64()
}

func (c *NoteContract) GetNoteItem(index int64) string {
	note, err := c.contract.Notes(nil, c.accountAddress, big.NewInt(index))
	if err != nil {
		log.Fatalf("getNoteItem: %v \n", err)
	}
	return note
}

func (c *NoteContract) UpdateNote(index int64, note string) *types.Transaction {
	tx, err := c.contract.ModifyNote(accountAuth(), c.accountAddress, big.NewInt(index), note)
	if err != nil {
		log.Fatalf("ModifyNote: %v \n", err)
	}
	return tx
}

func (c *NoteContract) AddNote(note string) *types.Transaction {
	tx, err := c.contract.AddNote(accountAuth(), note)
	if err != nil {
		log.Fatalf("AddNote: %v \n", err)
	}
	return tx
}
