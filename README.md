# Template Repo for JQR Calc Projects.

To create a blank repo for Trainees, create a new repo, use the "Import Project", select "Repo by URL", and set the URL to this repo.
You may be prompted to enter your DevForce credentials.

REMEMBER! You must also copy over the .gitlab-ci.yml and .clang-format files!

- The recommended order of completion is:
1. SimpleCalc
2. FileCalc
3. DataStructures1
4. ThreadCalc
5. NetCalc
- Each project is intended to be developed in it's own branch a merge request into master should be made when it is ready for review.
- If you are not getting updates pushed to your repo (indluding tests, revised documentation, and header files), please remind someone at CSD-T to push the latest updates to the master branch of your repo.
- If you see any errors, with anything inside, please make an issue.
- Be sure to check the updates branch frequently. This is rapidly changing product, and as we get feedback we integrate it. If docs don't make sense, ensure you dont have an old version.


# Update

All tests passed.

```console
ubuntu@ubuntu2004:~/Documents/jqr-calcprojects$ bash run_tests.sh 
Found build dir. Running tests...
Running tests...
Test project /home/ubuntu/Documents/jqr-calcprojects/build
    Start 1: TestSimpleCalc
1/5 Test #1: TestSimpleCalc ...................   Passed    0.20 sec
    Start 2: TestFileCalc
2/5 Test #2: TestFileCalc .....................   Passed    0.47 sec
    Start 3: TestDataStructures1
3/5 Test #3: TestDataStructures1 ..............   Passed    3.29 sec
    Start 4: TestThreadCalc
4/5 Test #4: TestThreadCalc ...................   Passed    1.30 sec
    Start 5: TestNetCalc
5/5 Test #5: TestNetCalc ......................   Passed    2.75 sec

100% tests passed, 0 tests failed out of 5

Total Test time (real) =   8.01 sec
```