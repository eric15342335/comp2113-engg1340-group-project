virtualenv _venv --clear
source _venv/scripts/activate
pip install cpp-coveralls

branches="`git branch -lr | cut -c 10- | cut -d ' ' -f 1 | grep -v HEAD`"

for branch in $branches
do
    echo $branch
    git checkout $branch
    make clean
    CXXFLAGS=--coverage make goto
    gcov src/*.cpp -o .
    coveralls
    rm *.gcda *.gcno *.gcov
done
