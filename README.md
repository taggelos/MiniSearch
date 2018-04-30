# MiniSearch

Mini search engine for keywords in files. Sentences are considered as documents (big in size).
Each document has the appropriate number starting from 0.

<b><i> Arguments: </i></b> <br/>
./minisearch -i docfile -k K  <br/>
./minisearch -i docfile (default value 10 gia to K)  <br/>
./minisearch -k K -i docfile  <br/>

<b><i> Commands: </i></b> <br/>
<b>/search q1, q2 .. q10</b> (search 1 to 10 words) <br/>
<b>/df</b>                   (document frequency of all words) <br/>
<b>/df q1</b>                (document frequency of specific word) <br/>
<b>/tf</b>                   (term frequency) <br/>

The score of each document was calculated using [bm25](https://en.wikipedia.org/wiki/Okapi_BM25)

The trie structure can be seen in the image below

![Image](images/architecture.png)
