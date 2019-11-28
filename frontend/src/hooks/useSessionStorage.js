import { useState, useEffect } from 'react';


const useSessionStorage = localStorageKey => {
    const [value, setValue] = useState(
        sessionStorage.getItem(localStorageKey) || ''
    );

    useEffect(() => {
        if (typeof value === 'object') {
            sessionStorage.setItem(localStorageKey, JSON.stringify(value));
        } else {
            sessionStorage.setItem(localStorageKey, value);
        }
    }, [value, localStorageKey]);

    return [value, setValue];
};

export default useSessionStorage;