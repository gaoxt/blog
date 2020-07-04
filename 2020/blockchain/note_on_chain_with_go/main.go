package main

import (
	"net/http"

	models "github.com/blogDemo/2020/blockchain/note_on_chain_with_go/models"
	"github.com/gin-gonic/gin"
)

func HomePage(c *gin.Context) {
	c.HTML(http.StatusOK, "index.tmpl", gin.H{})
}

func main() {
	router := gin.Default()

	router.LoadHTMLGlob("templates/*")
	router.Static("/src", "src")

	index := router.Group("/")
	{
		index.GET("/", HomePage)
		index.GET("/list", models.GetNoteList)
		index.POST("/add", models.InsertNote)
		index.POST("/update", models.UpdateNote)
	}
	router.Run(":4000")
}
