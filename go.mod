module github.com/envoyproxy/protoc-gen-validate

go 1.12

require (
	github.com/iancoleman/strcase v0.0.0-20180726023541-3605ed457bf7
	github.com/lyft/protoc-gen-star v0.5.3
	github.com/spf13/afero v1.3.4 // indirect
	golang.org/x/lint v0.0.0-20200302205851-738671d3881b
	golang.org/x/net v0.0.0-20200226121028-0de0cce0169b
	golang.org/x/tools v0.0.0-20200522201501-cb1345f3a375
	google.golang.org/protobuf v1.26.0
)

replace github.com/lyft/protoc-gen-star => github.com/sarthak40/protoc-gen-star v0.5.3-0.20210511152005-e0bab4844e07