package main

import (
	"fmt"
	"inbox/contracts"
	"io/ioutil"
	"log"
	"strings"

	"github.com/ethereum/go-ethereum/accounts/abi/bind"
	"github.com/ethereum/go-ethereum/ethclient"
)

const key = "UTC--2020-06-23T12-24-37.353894000Z--e0380828902269bfbce6b056ae3bfce8d52fd6a8"

func main() {
	blockchain, err := ethclient.Dial("http://127.0.0.1:8545")
	if err != nil {
		log.Fatalf("Unable to connect to network:%v \n", err)
	}

	// 合约部署
	data, _ := ioutil.ReadFile(key)
	auth, err := bind.NewTransactor(strings.NewReader(string(data)), "123456")
	if err != nil {
		log.Fatalf("Failed to create authorized transactor:%v \n", err)
	}
	address, _, _, err := contracts.DeployInbox(
		auth,
		blockchain,
		"Hello World",
	)
	if err != nil {
		log.Fatalf("deploy %v \n", err)
	}
	fmt.Printf("Contract pending deploy:0x%x \n", address)

	// 合约查看
	// contract, err := contracts.NewInbox(common.HexToAddress("0x3907dcd170a820b1ef8abdbd4545dfa29868d822"), blockchain)
	// if err != nil {
	// 	log.Fatalf("conn contract: %v \n", err)
	// }

	// fmt.Println(contract.Message(nil))

	// 合约设置
	// contract, err := contracts.NewInbox(common.HexToAddress("0x3907dcd170a820b1ef8abdbd4545dfa29868d822"), blockchain)
	// if err != nil {
	// 	log.Fatalf("conn contract: %v \n", err)
	// }
	// tx, err := contract.SetMessage(&bind.TransactOpts{
	// 	From:   auth.From,
	// 	Signer: auth.Signer,
	// 	Value:  nil,
	// }, "Hello Galaxy 2")
	// if err != nil {
	// 	log.Fatalf("set contract: %v \n", err)
	// }
	// fmt.Printf("tx sent: %s \n", tx.Hash().Hex())

	// fmt.Println(contract.Message(nil))

}
