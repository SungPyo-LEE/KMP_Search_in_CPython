# KMP_Search_in_CPython
## C로 씌여진 문자열 탐색, 파이썬으로 임베딩 하자

자연어 처리 된 문자를 문서에서 빠르게 찾기 위해 KMP 알고리즘을 적용. Python에서 탐색은 느려서 C로 임베딩 된 함수를 이용 해보자


## Build
* NUMPY installed Python Envs
```sh
$ python array_build.py build
and
$ python
and
>> import kmp_search
>> print(kmp_search.kmp_search("abcabadbadcdbabdbacbadbbacbacababadbbadda", "ab"))
```

## 인코딩
따로 인코딩 처리를 하지 않았다...! 영어는 잘 읽는데 한글 처리고 민

## 추가 예정
정규식을 이용하여 문서를 전처리 하는 방법을 생각 해보자

## 참고 사이트
* 참고: https://github.com/abonaca/streakline/blob/master/streak_wrap.c
* 참고2: https://scipy-cookbook.readthedocs.io/_downloads/C_arraytest.c
* 참고3: https://stackoverflow.com/questions/12582875/c-array-to-pyarray
* 참고4: http://notes.secretsauce.net/notes/2017/07/23_interfacing-numpy-and-c-an-example.html
* 참고5: http://scipy-lectures.org/advanced/interfacing_with_c/interfacing_with_c.html
* 공식 문서: https://docs.scipy.org/doc/numpy-1.14.0/reference/c-api.array.html
