package models

import (
	"net/http"
	"strconv"

	service "github.com/blogDemo/2020/blockchain/note_on_chain_with_go/service"
	"github.com/gin-gonic/gin"
)

func GetNoteList(c *gin.Context) {
	contract := service.NewNoteContract()
	notes := make([]string, contract.NoteLen)
	for i := contract.NoteLen - 1; i >= 0; i-- {
		notes[i] = contract.GetNoteItem(i)
	}
	c.JSON(http.StatusOK, gin.H{
		"code": http.StatusOK,
		"msg":  "success",
		"data": notes,
	})
}

type CreateContent struct {
	Note string `json:"note" binding:"required"`
}

func InsertNote(c *gin.Context) {
	var content CreateContent
	if err := c.ShouldBindJSON(&content); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"code": http.StatusBadRequest, "msg": err})
		return
	}
	contract := service.NewNoteContract()
	tx := contract.AddNote(content.Note)
	c.JSON(http.StatusOK, gin.H{
		"code": http.StatusOK,
		"msg":  "success",
		"data": tx,
	})
}

type UpdateContent struct {
	Index string `json:"index" binding:"required"`
	Note  string `json:"note" binding:"required"`
}

func UpdateNote(c *gin.Context) {
	var content UpdateContent
	if err := c.ShouldBindJSON(&content); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{"code": http.StatusBadRequest, "msg": err})
		return
	}
	contract := service.NewNoteContract()
	index, _ := strconv.ParseInt(content.Index, 10, 64)
	tx := contract.UpdateNote(index, content.Note)
	c.JSON(http.StatusOK, gin.H{
		"code": http.StatusOK,
		"msg":  "success",
		"data": tx,
	})
}
